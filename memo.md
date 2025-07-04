# minitalk との記録。

まずは、subject を読んでみる。

# minitalk

なんか、2 つ実行ファイル作成する必要があるっぽい。
client と server。
お〜ん。イマイチわからんなぁ。
どうしたらいいんやろ。

とりあえず、色々関数は使えそう。
シグナル使うのか？
あー、シグナル使うんやな。
server を先に起動する。
client を起動して、server にメッセージを送る。
文字列を送信して、それを受け取らなあかんのか。
PID は確かプロセス ID のこと。
getpid()で取得できるはず。→ 使用許可関数に含まれてるからそれで渡すのかなー。

え、これめっちゃ簡単ちゃう？文字送るだけやろ。
めっちゃ簡単そうやん。

あ、同時に複数のクライアントが接続してきたら全部並列処理しなアカンのか？

2 つのシグナルしか使用しちゃダメそう。
えー。めっちゃ簡単そうやけどな。難しいポイントどこなんやろ。
あーこれ、0, 1しか送れへんのか。
まあ、それが出来たら1bitずつ送信して終わりやな。

8bit受信して、文字化して、ってのを繰り返せば終わりそう。

signalのman, wiki, Qiitaを読んだ。
え、やっぱめっちゃ簡単そうやん。

# 使用許可関数

◦write
◦ft_printf or any equivalent YOU coded
◦signal
◦sigemptyset
◦sigaddset
◦sigaction
◦kill
◦getpid
◦malloc
◦free
◦pause
◦sleep
◦usleep
◦exit

とりあえず、これらの関数の理解度を上げる必要ある。

write, ft_printf, free, malloc はわかる。

ほかを結構詳しく調べてみる。

### signal

シグナルを処理するための関数。
あーー、なるほど。これでシグナルが送信されたときに、現在の処理を一時中断して、
異なる処理に分岐できるんや。
え、けどそれは新しいプロセスになってるってことなんか？
それとも、同じプロセスの中で処理を切り替えるってことなんかな。
うーん。送信できるなら受信もしたいよなー。
んじゃ、どうやったら違うプロセスにシグナルを送信できるんやろ。

とりあえず他の関数見るか。

### sigemptyset
signal.hに定義されている関数。
シグナルセットを初期化するための関数。
sigfullsetと対になる関数ぽい。
sigemptyset と sigfillset の共通点は、どちらもsignalを初期化する関数ということ。
sigemptyset と sigfillset の違いは、
sigemptyset は空のシグナルセットを作成するのに対し、sigfillset は全てのシグナルを含むシグナルセットを作成すること。

他にも、sigismember, sigaddset, sigdelset などがある。
ここで何度も出てきているsetというのは、集合を表す。→どういうふうに実装されているかがきになる。
俺が自分で実装するなら、signalはおそらく有限の個数なので、フラグを立てることで実装するかなぁ。

### sigaddset
シグナルセットにシグナルを追加するための関数。
sigemptysetで初期化したシグナルセットに、sigaddsetでシグナルを追加していくことで、
特定のシグナルを処理するためのシグナルセットを作成することができる。

### sigaction
manめっちゃながい。。。面倒くさい。
シグナルの処理方法を設定するための関数。
シグナルが送信されたときに、どの関数を呼び出すかを設定することができる。
シグナルが送信されたときに、どの関数を呼び出すかを設定するために、sigaction構造体を使用する。
まあそれぐらいでいいかな。

signal関数とsigaction関数の違いがきになるねぇ。
よう分からんけど、sigactionの方が細かい設定ができるっぽい。

sigactionの構造体について調べなあかんね。

```c
#include <signal.h>
struct sigaction {
    void     (*sa_handler)(int);
    void     (*sa_sigaction)(int, siginfo_t *, void *);
    sigset_t   sa_mask;
    int        sa_flags;
    void     (*sa_restorer)(void);
};
```
sa_handlerはシグナルが送信されたときに呼び出される関数を指定する。
sa_sigaction?
sa_maskはシグナルが送信されたときに、シグナルが送信されたときにブロックするシグナルを指定する。
sa_flagsは？
sa_restorerは？

よーわからん。

### kill
シグナルを送信するための関数。
プロセスにシグナルを送信するための関数。
プロセス ID を指定して、シグナルを送信することができる。
シグナルを送信するためには、プロセス ID を取得する必要がある。
getpid()関数を使用して、プロセス ID を取得することができるっぽい？
うーん、PIDの取得って一意にできるんかな？

### getpid
プロセス ID を取得するための関数。
プロセス ID は、プロセスを一意に識別するための番号。
プロセス ID は、システム上で一意。
getppid()関数もあるらしい。
getppid()は親プロセスのプロセス ID を取得するための関数。
getpid()は現在のプロセスのプロセス ID を取得するための関数。

まあこれぐらいで良いでしょう。

## 全体の構造。
いやー全然分からんなぁ。
とりあえず、server と client を実装して、シグナルを送受信するところから始めないと行けない。
てか、それが出来たらほぼ終わりやろ。
うーん。プロセスIDをどうやって取得すればいいか分からん。

順序は、まずserverを起動して、次にclientを起動する。
serverは、クライアントからの接続を待ち受ける。
クライアントは、サーバーのプロセスIDを指定して、接続する。←こいつがまじ分からん。
接続が確立したら、クライアントはサーバーにシグナルを送信する。← ここはkill関数を使うのかな？
サーバーは、シグナルを受信して、シグナルに対応する処理を実行する。→ここの処理はいけそ。

subject読んだら、いけそうな気がしてきた。
serverを起動したときに、getpid()でプロセスIDを取得して、それを出力すれば良いのか。
じゃあどうやって、clientにプロセスIDを受信するんやろ。
clientは、サーバーのプロセスIDを引数として受け取る。
あー、なるほど。clientはサーバーのプロセスIDを引数として受け取って、サーバーに接続するんやな。
サーバーは、クライアントからの接続を待ち受けて、接続が確立したら、クライアントにシグナルを送信する。

### 参考
- [minitalk](https://concrete-lion-c56.notion.site/Minitalk-126c6360e60c805f93b4e280366f3764)
- [【まとめ】signalについて](https://zenn.dev/hosu/articles/500079bf9be5fa)
- [medium](https://medium.com/@oduwoledare/42-minitalk-explained-5b236adc2c24)

あー、別にPIDの送受信簡単やん。
Serverファイルを実行して、プロセスID出力して、クライアントに渡すだけやん。
なんか、めっちゃ出来そう。

# serverの実装
とりあえず、serverの実装を始める。
server.cを作成して、必要なヘッダーファイルをインクルードする。
とりあえず、PIDの取得と出力をやってみる。
getpid()関数を使用して、プロセスIDを取得する。
これ返り値の構造体何？？pid_t型ってなんや？
- [C言語のpid_tを調べる](https://t0m00m0t.hatenablog.com/entry/2018/03/06/231110)

fcntl.hに定義されていた。
```c
#ifndef __pid_t_defined
typedef __pid_t pid_t;
# define __pid_t_defined
#endif
```
__pid_tは??
```c
kei2003730@JikuPC ~/A/4/w/src (master)> grep -rnw /usr -e '__pid_t'
/usr/include/x86_64-linux-gnu/bits/types.h:154:__STD_TYPE __PID_T_TYPE __pid_t; /* Type of process identifications.  */
```

__PID_T_TYPEは？
```c
kei2003730@JikuPC ~/A/4/w/src (master) [SIGINT]> grep -rnw /usr -e '__PID_T_TYPE'
/usr/include/x86_64-linux-gnu/bits/typesizes.h:53:#define __PID_T_TYPE          __S32_TYPE
```

__S32_TYPEは？
```c
/usr/include/x86_64-linux-gnu/bits/types.h:111:#define  __S32_TYPE              int
```
intかーい。


### やること。
- [x] server のPID取得
- [x] server のPID出力
- [ ] client のPID取得
- [ ] client → server にシグナル送信
- [ ] server で受信

- [ ] client の取得文字を2進数に変換。
