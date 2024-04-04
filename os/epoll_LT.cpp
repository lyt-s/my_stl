#include <fcntl.h>
#include <netdb.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/epoll.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <time.h>
#include <unistd.h>
#define COUNT 1
int mode = 0;
int slp = 0;

int pid[COUNT] = {0};
int count = 0;
void server(int epfd) {
  struct epoll_event *events;
  int num, i;
  struct timespec ts;
  events = (epoll_event *)calloc(64, sizeof(struct epoll_event));
  while (1) {
    int sd, csd;
    struct sockaddr in_addr;
    num = epoll_wait(epfd, events, 64, -1);
    if (num <= 0) {
      continue;
    }/*        ts.tv_sec = 0;        ts.tv_nsec = 1;        if(nanosleep(&ts, NULL) != 0) {            perror("nanosleep");            exit(1);        }        */// 用于测试ET模式下丢事件的情况if (slp) {            sleep(slp);        }

    sd = events[0].data.fd;
    socklen_t in_len = sizeof(in_addr);

    csd = accept(sd, &in_addr, &in_len);
    if (csd == -1) {  // 打印这个说明中了epoll
      // LT惊群的招了。
      printf("xxxxxxxxxxxxxxxxxxxxxxxxxx:%d\n", getpid());
      continue;
    }  //
       // 本进程一共成功处理了多少个请求。
    count++;
    printf("get client:%d\n", getpid());
    close(csd);
  }
}

static void siguser_handler(int sig) {  //
  // 在主进程被Ctrl-C退出的时候，每一个子进程均要打印自己处理了多少个请求。
  printf("pid:%d       count:%d\n", getpid(), count);
  exit(0);
}

static void sigint_handler(int sig) {
  int i = 0;
  // 给每一个子进程发信号，要求其打印自己处理了多少个请求。

  for (i = 0; i < COUNT; i++) {
    kill(pid[i], SIGUSR1);
  }
}

int main(int argc, char *argv[]) {
  int ret = 0;
  int listener;
  int c = 0;
  struct sockaddr_in saddr;
  int port;
  int status;
  int flags;
  int epfd;
  struct epoll_event event;
  if (argc < 4) {
    exit(1);
  }  // 0为LT模式，1为ET模式
  mode = atoi(argv[1]);
  port = atoi(argv[2]);  //
  // 是否在处理accept之前耽搁一会儿，这个参数更容易重现问题
  slp = atoi(argv[3]);
  signal(SIGINT, sigint_handler);
  listener = socket(PF_INET, SOCK_STREAM, 0);
  saddr.sin_family = AF_INET;
  saddr.sin_port = htons(port);
  saddr.sin_addr.s_addr = INADDR_ANY;
  bind(listener, (struct sockaddr *)&saddr, sizeof(saddr));
  listen(listener, SOMAXCONN);
  flags = fcntl(listener, F_GETFL, 0);
  flags |= O_NONBLOCK;
  fcntl(listener, F_SETFL, flags);
  epfd = epoll_create(64);
  if (epfd == -1) {
    perror("epoll_create");
    abort();
  }
  event.data.fd = listener;
  event.events = EPOLLIN;
  if (mode == 1) {
    event.events |= EPOLLET;
  } else if (mode == 2) {
    event.events |= EPOLLONESHOT;
  }
  ret = epoll_ctl(epfd, EPOLL_CTL_ADD, listener, &event);
  if (ret == -1) {
    perror("epoll_ctl");
    abort();
  }
  for (c = 0; c < COUNT; c++) {
    int child;
    child = fork();
    if (child == 0) {  // 安装打印count值的信号处理函数
      signal(SIGUSR1, siguser_handler);
      server(epfd);
    }
    pid[c] = child;
    printf("server:%d  pid:%d\n", c + 1, child);
  }
  wait(&status);
  sleep(1000000);
  close(listener);
  return 0;
}