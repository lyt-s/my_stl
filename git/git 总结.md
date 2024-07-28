# git 总结

1. git init

2. 生成ssh

   1. ssh-keygen

   2. ```bash
      $ ssh-keygen -t ed25519 -C "1814666859@qq.com"
      #如果您使用的是不支持 Ed25519 算法的旧系统，请使用：
      
      $ ssh-keygen -t rsa -b 4096 -C "your_email@example.com"
      ```

3. // 配置user.name
   git config --global user.name "your user name"
   // 配置user.email
   git config --global user.email "your user email"
   // 查看配置
   git config --list

   ```
   git config --global user.name "lyt-s"
   git config --global user.email "1814666859@qq.com"
   
   
   git push -u origin "master"
   ```

4. git remote

   1. `git remote add origin https://gitee.com/L-creater/cv.git`

      你可以在命令行中使用字符串 origin 来代替整个 URL。

5. git clone

6. git fetch

   1. 这个命令会访问远程仓库，从中拉取所有你还没有的数据。 执行完成后，你将会拥有那个远程仓库中所有分支的引用，可以随时合并或查看。

   2. 注意 git fetch 命令只会将数据下载到你的本地仓库——它并不会自动合并或修改你当前的工作。 当准备好时你必须手动将其合并入你的工作。

   **将某个远程主机的更新**

   ```shell
   $ git fetch <远程主机名>
   Shell
   ```

   要更新所有分支，命令可以简写为：

   ```shell
   $ git fetch
   Shell
   ```

   上面命令将某个远程主机的更新，全部取回本地。默认情况下，`git fetch`取回所有分支的更新。如果只想取回特定分支的更新，可以指定分支名,如下所示 -

   ```shell
   $ git fetch <远程主机名> <分支名>
   Shell
   ```

   比如，取回`origin`主机的`master`分支。

   ```shell
   $ git fetch origin master
   Shell
   ```

   所取回的更新，在本地主机上要用”远程主机名/分支名”的形式读取。比如`origin`主机的`master`分支，就可以用`origin/master`读取。

   `git branch`命令的`-r`选项，可以用来查看远程分支，`-a`选项查看所有分支。

   ```shell
   $ git branch -r
   origin/master
   
   $ git branch -a
   * master
     remotes/origin/master
   Shell
   ```

   上面命令表示，本地主机的当前分支是`master`，远程分支是`origin/master`。

   取回远程主机的更新以后，可以在它的基础上，使用git checkout命令创建一个新的分支。

   ```
   git checkout -b newBrach origin/master
   ```

   上面命令表示，在`origin/master`的基础上，创建一个新分支:*newBrach*。

   此外，也可以使用`git merge`命令或者`git rebase`命令，在本地分支上合并远程分支。

   ```shell
   $ git merge origin/master
   # 或者
   $ git rebase origin/master
   Shell
   ```

   上面命令表示在当前分支上，合并`origin/master`。

7. git pull

   将远程指定分支 拉取到 本地指定分支上：

   ```bash
   git pull origin <远程分支名>:<本地分支名>
   #（注：命令里的尖括号<>只是包裹中文的标识，方便你看的，实际使用时不用写，不过冒号需要）
   ```

   将远程指定分支 拉取到 本地当前分支上：

   ```
   git pull origin <远程分支名>
   ```

   将与本地当前分支同名的远程分支 拉取到 本地当前分支上(需**先关联远程分支)**  --

   将本地分支与远程同名分支相关联 --- git push -u origin <本地分支名>

   ```
   git pull
   ```

   在克隆远程项目的时候，本地分支会自动与远程仓库建立追踪关系，可以使用默认的origin来替代远程仓库名

   - 通常会从最初克隆的服务器上抓取数据并自动尝试合并到当前所在的分支。

   - 在大多数情况下它的含义是一个 git fetch 紧接着一个git merge 命令

8. git add

9. .gitignore

   1. 将要忽略的文件

   2. • 所有空行或者以注释符号 ＃ 开头的行都会被 Git 忽略。
      • 可以使用标准的 glob 模式匹配。
      • 匹配模式最后跟反斜杠（ / ）说明要忽略的是目录。
      • 要忽略指定模式以外的文件或目录，可以在模式前加上惊叹号（ ! ）取反。

   3.

      ```c
      #此为注释 – 将被 Git 忽略
      
      *.a # 忽略所有 .a 结尾的文件
      !lib.a # 但 lib.a 除外
      /TODO # 仅仅忽略项目根目录下的 TODO 文件，不包括 subdir/TODO
      build/ # 忽略 build/ 目录下的所有文件
      doc/*.txt # 会忽略 doc/notes.txt 但不包括 doc/server/arch.txt
      ```

10. git commit -m

11. 提交更新

12. git commit -a

13. 跳过  git add
14. 自动把所有已经跟踪过的文件暂存起来一并提交

15. git status

16. gi

17. git checkout  A分支

18. --切换到对应A分支

19. git branch  A分支
    1. -- 新建A分支

20. git checkout -b  A分支
    1. 新建A分支，并切换到A分支

21. git branch -d  A分支
    1. 删除A分支

22. git branch -v
    1. 查看各个分支最后一次commit信息

23. git branch --merged
    1. 查看那些分支已被并入当前分支

24. git branch --no-merged
    1. 查看尚未合并的工作

25. git diff

    1. 查看尚未保存的文件更新了那部分

26. git diff --cached
    git diff --staged ，

    1. 要看已经暂存起来的文件和上次提交时的快照之间的差异

27. git mv

28. git log

29. git push

将本地当前分支 推送到 远程指定分支上（注意：pull是远程在前本地在后，push相反）：

``` bash
git push origin <本地分支名>:<远程分支名>
```

将本地当前分支 推送到 与本地当前分支同名的远程分支上（注意：pull是远程在前本地在后，push相反

``` bash
git push origin <本地分支名>
```

将本地当前分支 推送到 与本地当前分支同名的远程分支上(需先关联远程分支，方法见文章末尾)

```bash
git push
```

将本地分支与远程同名分支相关联

```
git push -u origin <本地分支名>
```

1. git push origin  :A
    1. 删除远程分支 A\

2. git push origin --delete serverfix

    1. 基本上这个命令做的只是从服务器上移除这个指针。 Git 服务器通常会保留数据一段时间直到垃圾回收运行，所以如果不小心删除掉了，通常是很容易恢复的。

3. git remove

    1. 移除文件操作
    2. 如果删除之前修改过并且已经放到暂存区域的话，则必须
       要用强制删除选项-f

4. git remove --cached

    1. 把文件从 Git 仓库中删除（亦即从暂存区域移除），但仍然希望保留在当前工作目录中。

5. git show

## 变基

---整合分支

变基的基本操作

![image-20230411091016025](/home/ly/.config/Typora/typora-user-images/image-20230411091016025.png)

1. 整合分支最容易的方法是 merge 命令。 它会把两个分支的最新快照（C3 和 C4）以及二者最近的共同祖先（C2）进行三方合并，合并的结果是生成一个新的快照（并提交）。

2. 你可以提取在 C4 中引入的补丁和修改，然后在 C3 的基础上应用一次。 在 Git 中，这种操作就叫做 变基（rebase）。 你可以使用 rebase 命令将提交到某一分支上的所有修改都移至另一分支上，就好像“重新播放”一样。

   ```
   //你可以检出 experiment 分支，然后将它变基到 master 分支上：
   $ git checkout experiment
   $ git rebase master
   
   ```

   ![image-20230411091517729](/home/ly/.config/Typora/typora-user-images/image-20230411091517729.png)

3. 它的原理是首先找到这两个分支（即当前分支 experiment、变基操作的目标基底分支 master） 的最近共同
   祖先 C2，然后对比当前分支相对于该祖先的历次提交，提取相应的修改并存为临时文件， 然后将当前分支指向
   目标基底 C3, 最后以此将之前另存为临时文件的修改依序应用。

4. 最后---将 C4 中的修改变基到 C3 上现在回到 master 分支，进行一次快进合并。

5. ```
   git checkout master
   git merge experiment
   ```

   ![image-20230411091531521](/home/ly/.config/Typora/typora-user-images/image-20230411091531521.png)

1. git rebase --onto master server client
   1. 取出 client 分支，找出它从 server 分支分歧之后的补丁， 然后把这些补丁在master 分支上重放一遍，让 client 看起来像直接基于 master 修改一样”。这理解起来有一点复杂，不过效果非常酷。

# 错误

```
>>>git push 2023 master 

Username for 'https://github.com': L-creater
Password for 'https://L-creater@github.com': 
remote: Support for password authentication was removed on August 13, 2021.
remote: Please see https://docs.github.com/en/get-started/getting-started-with-git/about-remote-repositories#cloning-with-https-urls for information on currently recommended modes of authentication.
fatal: 'https://github.com/L-creater/2023.git/' 鉴权失败
```

-- 个人访问令牌

- 只需创建一个 ssh 密钥并将它们添加到您的 github acc
- help: [Create ssh key](https://docs.github.com/en/authentication/connecting-to-github-with-ssh/generating-a-new-ssh-key-and-adding-it-to-the-ssh-agent)在此页面上，首先选择您的操作系统，然后按照以下步骤操作
- [将新的 SSH 密钥添加到您的 GitHub 帐户](https://docs.github.com/en/authentication/connecting-to-github-with-ssh/adding-a-new-ssh-key-to-your-github-account)
- 最后，使用 ssh 链接而不是 http 克隆 repos

## error:<git@github.com>'s password

有时，防火墙会完全拒绝允许 SSH 连接。 如果无法选择使用[具有凭据缓存的 HTTPS 克隆](https://docs.github.com/zh/github/getting-started-with-github/caching-your-github-credentials-in-git)，可以尝试使用通过 HTTPS 端口建立的 SSH 连接克隆。 大多数防火墙规则应允许此操作，但代理服务器可能会干扰。

要测试通过 HTTPS 端口的 SSH 是否可行，请运行以下 SSH 命令：

```bash
$ ssh -T -p 443 git@ssh.github.com
> Hi USERNAME! You've successfully authenticated, but GitHub does not
> provide shell access.
```

如果这样有效，万事大吉！ ---执行接下来的操作

启用通过 HTTPS 的 SSH 连接
如果你能在端口 443 上通过 SSH 连接到 <git@ssh.github.com>，则可覆盖你的 SSH 设置来强制与 GitHub.com 的任何连接均通过该服务器和端口运行。

要在 SSH 配置文件中设置此行为，请在 ~/.ssh/config 编辑该文件，并添加以下部分：

```
Host github.com
Hostname ssh.github.com
Port 443
User git
```

# 拉取远程分支

现在本地新建分支，在进行拉取

一、pull操作

1. 将远程指定分支拉取到本地指定分支上： git pull origin <远程分支名>:<本地分支名>
2. 将远程指定分支拉取到本地当前分支上： git pull origin <远程分支名>
3. 将与本地当前分支同名的远程分支拉取到本地当前分支上(需先关联远程分支，方法**git push --set-upstream origin <本地分支名>**)
