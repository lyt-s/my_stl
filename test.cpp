// #include <iostream>
// class Parent {
//  public:
//   Parent() { std::cout << "1"; }
//   Parent(const Parent &p) { std::cout << "2"; }
//   const Parent &operator=(const Parent &p) {
//     std::cout << "3";
//     return *this;
//   }
// };
// int main() {
//   Parent p;
//   Parent p1(p);
//   Parent p2 = p;
//   p2 = p1;
// }
#include <iostream>
#include <thread>
#include <utility>
#include <vector>
class E {
 public:
  virtual void func(int i = 0) { std::cout << "E::func()\t" << i << "\n"; }
};
class F : public E {
 public:
  virtual void func(int i = 1) { std::cout << "F::func()\t" << i << "\n"; }
};

#include <stdio.h>

int inc(int a) { return (++a); }

int multi(int* a, int* b, int* c) { return (*c = *a * *b); }
typedef int (*FUNC1)(int in);
typedef int (*FUNC2)(int*, int*, int*);

void show(FUNC2 fun, int arg1, int* arg2) {
  FUNC1 p = &inc;
  int temp = p(arg1);
  fun(&temp, &arg1, arg2);
  printf(" %d\n", *arg2);
}

int main() {
  int a;
  show(multi, 10, &a);
  int i = 8;
  int j = 9;
  int& x = i;
  i = std::move(j);  // 就是拷贝，因为 int 没有移动构造函数
  std::cout << x << std::endl;
  std::cout << i << std::endl;
  std::cout << j << std::endl;
  return 0;
}

// #include <string.h>

// #include <cstdio>
// #include <cstdlib>

// int main() {
//   char src[] = "hello, world";
//   char* dest = NULL;
//   int len = strlen(src);
//   dest = (char*)malloc(len + 1);  // 分配 len+1 个字节的内存
//   char* d = dest;
//   char* s = src + len - 1;         // 指向 src 的最后一个字符
//   while (len-- != 0) *d++ = *s--;  // 逐个复制字符
//   *d = '\0';                       // 添加结束符
//   printf("%s", dest);
//   free(dest);  // 释放动态分配的内存
//   return 0;
// }

namespace detection {
class Detect {
  friend void thread_start(Detect* p);

 public:
  Detect();
  ~Detect();
  int get_fd_write() const { return m_fd_write; }
  int get_tid() const { return m_tid; }
  bool init(int, int);
  std::thread::id run();

 private:
  int m_fd_write;
  int m_tid;
};
}  // namespace detection


void ObjectDetector::Postprocess(
  const std::vector<cv::Mat> mats,
  std::vector<PaddleDetection::ObjectResult> *result,
  std::vector<int> bbox_num, std::vector<float> output_data_,
  std::vector<int> output_mask_data_, bool is_rbox = false) {
  result->clear();
  int start_idx = 0;
  int total_num = std::accumulate(bbox_num.begin(), bbox_num.end(), 0);
  int out_mask_dim = -1;
  if (config_.mask_) {
    out_mask_dim = output_mask_data_.size() / total_num;
  }

  for (int im_id = 0; im_id < mats.size(); im_id++) {
    cv::Mat raw_mat = mats[im_id];

    }

}

void ObjectDetector::Predict(const std::vector<cv::Mat> imgs, const double threshold,
             const int warmup, const int repeats,
             std::vector<PaddleDetection::ObjectResult>* result,
             std::vector<int>* bbox_num, std::vector<double>* times) {
  auto preprocess_start = std::chrono::steady_clock::now();
  int batch_size = imgs.size();

  // in_data_batch
  std::vector<float> in_data_all;
  std::vector<float> im_shape_all(batch_size * 2);
  std::vector<float> scale_factor_all(batch_size * 2);
  std::vector<const float*> output_data_list_;
  std::vector<int> out_bbox_num_data_;
  std::vector<int> out_mask_data_;

  // these parameters are for neo-yolo output
  std::vector<float> out_score_data_;
  std::vector<uint8_t> out_global_mask_data_;
  std::vector<int64_t> out_label_data_;

  // in_net img for each batch
  std::vector<cv::Mat> in_net_img_all(batch_size);

  // Preprocess image
  for (int bs_idx = 0; bs_idx < batch_size; bs_idx++) {
    cv::Mat im = imgs.at(bs_idx);
    Preprocess(im);
    im_shape_all[bs_idx * 2] = inputs_.im_shape_[0];
    im_shape_all[bs_idx * 2 + 1] = inputs_.im_shape_[1];

    scale_factor_all[bs_idx * 2] = inputs_.scale_factor_[0];
    scale_factor_all[bs_idx * 2 + 1] = inputs_.scale_factor_[1];

    in_data_all.insert(in_data_all.end(), inputs_.im_data_.begin(),
                       inputs_.im_data_.end());

    // collect in_net img
    in_net_img_all[bs_idx] = inputs_.in_net_im_;
  }
}