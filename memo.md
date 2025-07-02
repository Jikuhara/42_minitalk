# FDFとの記録。
まずは、subjectを読んでみる。

噂に聞いていたように、グラフィックをなんちゃらかんちゃら、するやつっぽい。
とりあえず、minilibxを使えるようになりたい。

## minilibxの使い方を調べる。
### minilibxのInstall方法
```
Install MinilibX

 - no installation script is provided. You may want to install
     - libmlx.a and/or libmlx_$(HOSTTYPE).a in /usr/X11/lib or /usr/local/lib
     - mlx.h in /usr/X11/include or /usr/local/include
     - man/man3/mlx*.1 in /usr/X11/man/man3 or /usr/local/man/man3
```
これがインストール方法っぽい。
libmlx.a or libmlx_$(HOSTTYPE).aを/usr/X11/lib or /usr/local/libに入れたらいいっぽい。
/usr/X11/ と /usr/local/ がわからないので、次はそれを調べてみるか。

### /usr/X11/ と /usr/local/ って何？
/usr/X11/ と /usr/local/ は、Unix系のシステムでよく使われるディレクトリのパス。
- `/usr/X11/` は、X Window Systemの関連ファイルが格納されるディレクトリ。
X Window Systemは、Unix系システムでGUIを提供するためのシステム。
今は廃止されているっぽい。

- `/usr/local/` は、システム全体で使用されるローカルのアプリケーションやライブラリが格納されるディレクトリ。
OSのupdateの影響を受けない。
とりあえず、ここに入れておけば大丈夫っぽい？

/usr/local/libにコピーしたいが、Permissonエラーが出る。なんで？
#### Permissionエラーが出る理由
/usr/local/は、root権限が必要なディレクトリだから。
どうしたら良いものか。

### とりあえず、minilibxを使えるようにする。
```
kjikuhar@c2r9s2 ~/42_FDF/test % cc sandbox_for_minilibx.c libmlx.a -I ../minilibx-linux/mlx.h
/usr/bin/ld: libmlx.a(mlx_init.o): in function `mlx_int_deal_shm':
mlx_init.c:(.text+0x30): undefined reference to `XShmQueryVersion'
/usr/bin/ld: mlx_init.c:(.text+0xe4): undefined reference to `XShmPixmapFormat'
/usr/bin/ld: libmlx.a(mlx_init.o): in function `mlx_init':
mlx_init.c:(.text+0x1f4): undefined reference to `XOpenDisplay'
/usr/bin/ld: mlx_init.c:(.text+0x288): undefined reference to `XInternAtom'
/usr/bin/ld: mlx_init.c:(.text+0x29f): undefined reference to `XInternAtom'
/usr/bin/ld: mlx_init.c:(.text+0x2f1): undefined reference to `XCreateColormap'
/usr/bin/ld: libmlx.a(mlx_int_get_visual.o): in function `mlx_int_get_visual':
mlx_int_get_visual.c:(.text+0x67): undefined reference to `XGetVisualInfo'
```
うーん、なんか上手く参照されていない。
Headerをもう少し見てみる。

```c
/*
** FR msg - FR msg - FR msg
**
** La MinilibX utilise 2 librairies supplementaires qu'il
**      est necessaire de rajouter a la compilation :
**   -lmlx -lXext -lX11
**
** La MinilibX permet le chargement des images de type Xpm.
** Notez que cette implementation est incomplete.
** Merci de communiquer tout probleme de chargement d'image
** de ce type.
*/
```
どうやら、`-lXext -lX11`を付ける必要があるっぽい。

```
kjikuhar@c2r9s2 ~/42_FDF/test % cc -lXext -lx11 sandbox_for_minilibx.c libmlx.a -I ../minilibx-linux/mlx.h
/usr/bin/ld: cannot find -lx11: No such file or directory
clang: error: linker command failed with exit code 1 (use -v to see invocation)
kjikuhar@c2r9s2 ~/42_FDF/test % cc -lXext sandbox_for_minilibx.c libmlx.a -I ../minilibx-linux/mlx.h
/usr/bin/ld: libmlx.a(mlx_init.o): undefined reference to symbol 'XInternAtom'
/usr/bin/ld: /lib/x86_64-linux-gnu/libX11.so.6: error adding symbols: DSO missing from command line
clang: error: linker command failed with exit code 1 (use -v to see invocation)
```

よ〜わからんて！！！
chatGPTに聞いてみる。

大文字小文字間違えてただけっぽい。アホすぎ。
```
kjikuhar@c2r9s2 ~/42_FDF/test % cc -lXext -lx11 -lmlx sandbox_for_minilibx.c libmlx.a -I ../minilibx-linux/mlx.h
/usr/bin/ld: cannot find -lx11: No such file or directory
/usr/bin/ld: cannot find -lmlx: No such file or directory
clang: error: linker command failed with exit code 1 (use -v to see invocation)
kjikuhar@c2r9s2 ~/42_FDF/test % cc -lXext -lX11 -lmlx sandbox_for_minilibx.c libmlx.a -I ../minilibx-linux/mlx.h
/usr/bin/ld: cannot find -lmlx: No such file or directory
clang: error: linker command failed with exit code 1 (use -v to see invocation)
kjikuhar@c2r9s2 ~/42_FDF/test % cc -lXext -lX11 sandbox_for_minilibx.c libmlx.a -I ../minilibx-linux/mlx.h
kjikuhar@c2r9s2 ~/42_FDF/test % ./a.out
0x1ef3a2a0
```
```c
#include <stdio.h>
#include "../minilibx-linux/mlx.h"

int main(int argc, char const *argv[])
{
	printf("%p\n", mlx_init());
	return (0);
}
```

できた！！！


### 実際にminilibxを使ってみる。
```c
/*
** Basic actions
*/

void	*mlx_new_window(void *mlx_ptr, int size_x, int size_y, char *title);
/*
**  return void *0 if failed
*/
```
これ使ってみる。
第一引数は、mlx_init()で得られたポインタを渡すっぽい。
size_x, size_yは、ウィンドウのサイズかな。
titleは知らんが適当に文字列を渡しときゃええやろ。const char * ちゃうんや。きになるなぁ。
```c
#include <stdio.h>
#include "../minilibx-linux/mlx.h"

int main(int argc, char const *argv[])
{
	void *mlx_ptr = mlx_init();
	printf("%p\n", mlx_ptr);
	void *mlx_success = mlx_new_window(mlx_ptr, 100, 100, "test_title");
	printf("%p\n", mlx_success);
	return (0);
}
```

```c
kjikuhar@c2r9s2 ~/42_FDF/test % cc -lXext -lX11 sandbox_for_minilibx.c libmlx.a -I ../minilibx-linux/mlx.h
kjikuhar@c2r9s2 ~/42_FDF/test % ./a.out
0x360d42a0
0x360e9b30
```

良さげですねぇ。

2025/06/28の進捗

```c
#include "../minilibx-linux/mlx.h"
#include <stdio.h>

int	main(void)
{
	void *mlx;
	void *win;

	mlx = mlx_init();
	if (mlx == NULL)
	{
		printf("Initialization failed\n");
		return (1);
	}
	win = mlx_new_window(mlx, 200, 200, "Hello world!");
	int count = 200;
	for (int i = 0; i < count; i++)
	{
		for (int j = 0; j < count; j++)
		{
			mlx_pixel_put(mlx, win, i, j, 0x00FFFFFF - i);
		}
	}
	mlx_string_put(mlx, win, 0, 0, 0x00FFFFFF, "42Tokyo");
	mlx_loop(mlx);
	return (0);
}
```

色変化のある、正方形の出力が出来た。
また、文字の出力も出来た。

PDFの読み込みを行った。
やるべきことは主に3つ。

## INPUTの実装
1. 入力のvalidationをおこなう。
2. 入力されたmap情報を2次元配列に格納する。
   1. get_next_lineを使って、1行ずつ読み込む。
   2. ft_splitを使用して、読み込んだ行をスペースで分割する。

どれぐらいのサイズが来るかわからないので、必ずmallocを使用する必要がある。

### mallocのサイズどうしようか問題。
get_next_lineを1回呼び出して、サイズを確認する必要あり？→これで横の大きさは確認できそう。
縦のline数がわからんねぇ。どうしたらいいんやろ。fileを読み込んだ瞬間わかったりするんかなぁ。
readのバイト数を数えたら行ける？ワンちゃんいけそうではある。

## OUTPUTの実装
やることは3つ。
1. windowの準備をする。
   1. mlx_init()で、minilibxの初期化を行う。
   2. mlx_new_window()で、ウィンドウを作成する。
   3. mlx_pixel_put()で、各点を描画する。←imageを使用したほうが処理が軽そう。
   4. loop待機。
   5. ESCやマウス処理の実装←BONUS範囲。
2. 視点に合わせて、各点の座標を変換する。
   1. 言うたら3次元を2次元に射影する的なね。
3. 各点を線で結ぶ。
   1. z座標は色を変更する必要がある。

視点の回転と、物体の回転、どっちを行うべきか。
firas曰く、objectが1つなので、これらは等価。そりゃそうか。相対的な位置関係は変わらないので。

これToDoリストうまいこと、githubで管理できる気がするんやけど、どうなんやろ。
githubのissueを使うのが良いのかなぁ。

まあいいや。

やることをまとめる。

# FDF ToDoリスト

## INPUT実装

### ファイル読み込み
- [x] 入力のvalidationを行う
  - [x] ファイルが存在するかチェック
  - [x] .fdf拡張子のチェック
  - [x] ファイルが読み込み可能かチェック
- [x] map情報を2次元配列に格納する
  - [x] get_next_lineを使って1行ずつ読み込む
  - [x] ft_splitを使用して読み込んだ行をスペースで分割する
  - [x] 数値文字列をint型に変換
  - [ ] メチャデカ数字対応

### メモリ管理
- [x] mallocのサイズ問題を解決する
  - [x] 1パス目：行数と列数をカウント
  - [x] 2パス目：実際のデータを格納
  - [ ] または動的配列（realloc）を使用
- [x] メモリリークの防止
  - [x] エラー時の適切なfree処理
  - [x] 正常終了時のfree処理

## OUTPUT実装

### 1. Window準備
- [x] mlx_init()でminilibxの初期化を行う
- [x] mlx_new_window()でウィンドウを作成する
- [x] imageを使用した描画システムの実装
  - [x] mlx_new_image()でイメージ作成
  - [x] mlx_get_data_addr()でデータアドレス取得
  - [x] mlx_put_image_to_window()で画面に描画
- [x] loop待機の実装
- [x] ESCやマウス処理の実装（BONUS範囲）
  - [x] ESCキーでプログラム終了
  - [x] ×ボタンでプログラム終了

### 2. 座標変換
- [x] 視点に合わせて各点の座標を変換する
  - [x] アイソメトリック投影の実装
  - [x] 3次元から2次元への射影計算
  - [x] ウィンドウサイズに合わせたスケーリング
  - [x] 画面中央への配置調整

### 3. 線描画
- [x] 各点を線で結ぶ
  - [x] ブレゼンハムアルゴリズムの実装
  - [x] 水平方向の隣接点接続
  - [x] 垂直方向の隣接点接続
- [x] z座標に応じた色変更
  - [x] 高度による色のグラデーション
  - [x] 色計算アルゴリズムの実装

## プロジェクト管理

### 開発環境
- [x] Makefileの作成
  - [x] minilibxライブラリのリンク設定
  - [x] 必須ルール（NAME, all, clean, fclean, re）
  - [x] 適切なコンパイルフラグ設定
- [x] ヘッダーファイルの作成
- [x] プロジェクト構造の整理

### テスト・デバッグ
- [ ] 42.fdfファイルでの動作確認
- [ ] エラーケースのテスト
- [ ] メモリリーク検査（valgrind）
- [ ] ノルムチェック

とりあえず、makefileを作成して、minilibxのライブラリをリンクできるようにする。
```makefile

一旦終わった！
あとは、視点回転、投射法の追加、＋１かな。
