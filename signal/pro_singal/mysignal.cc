#include <iostream>
#include <unistd.h>
#include <sys/types.h>
#include <signal.h>
#include <vector>


#define NUM_SIG 32
// int sigemptyset(sigset_t *set);
// int sigfillset(sigset_t *set);
// int sigaddset(sigset_t *set, int signum);
// int sigdelset(sigset_t *set, int signum);
// int sigismember(const sigset_t *set, int signum);

// int sigprocmask(int how, const sigset_t* set, sigset_t* oset);
// int sigpending(sigset_t* set);


std::vector<int> sig_vec = {2, 3};

void print_sig(const sigset_t& set){
  for(int i = NUM_SIG; i >= 1; --i){
    if(sigismember(&set, i)){
      std::cout << '1';
    }
    else std::cout << '0';
  }
  std::cout << std::endl;
}

void handle(int signo){
  std::cout << "信号编号：" << signo << " has been called." << std::endl;
}

void set_signal(sigset_t set, sigset_t out_set){
  for(const auto& it : sig_vec) sigaddset(&set, it); // ctrl + c
  for(const auto& it : sig_vec) signal(it, handle); // ctrl + c
  sigprocmask(SIG_SETMASK, &set, &out_set); // 设置阻塞信号
}

int main(){
  sigset_t set, out_set;

  // 清空信号
  sigemptyset(&set);
  sigemptyset(&out_set);
  
  set_signal(set, out_set);

  // for(const auto& it : sig_vec) sigaddset(&set, it); // ctrl + c
  // for(const auto& it : sig_vec) signal(it, handle); // ctrl + c
  // sigprocmask(SIG_SETMASK, &set, &out_set); // 设置阻塞信号

  int cnt = 10;
  int ans = 0;
  while(1){
    sigpending(&set);
    print_sig(set);
    if(!(cnt--)){
      sigprocmask(SIG_SETMASK, &out_set, &set); // 清除阻塞信号
      set_signal(set, out_set);
      cnt = 10;
      ans++;
      if(ans == 3) kill(getpid(), 9);
      std::cout << std::endl << "ans = " << ans << std::endl;
    }
    else std::cout << std::endl << "cnt = " << cnt << std::endl;
    sleep(1);
  }

  return 0;
}
