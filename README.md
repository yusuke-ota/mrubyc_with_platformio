# mrubyc_with_platformio

mruby/cをplatformioでビルドする

## 依存

- PlatformIO 4.x
  - Python 3.x

- mruby/c 1.2
  - mruby 2.0.1
  - ruby 2.x

## 使い方

### 初期設定

1. 作業用フォルダを作成、移動

~~~pwsh
mkdir your_work_space
cd .\your_work_space
~~~

2. 作業フォルダ内でPlatformIOで開発環境の設定

~~~pwsh
cd ..
pio init --ide your_ide_id --board your_board_ide
~~~

3. libフォルダ内でmrubycのリポジトリをクローン

~~~pwsh
cd ./lib
git clone https://github.com/mrubyc/mrubyc.git
~~~

4. 作業用フォルダ内でこのリポジトリをクローン

~~~pwsh
cd ..
git clone https://github.com/yusuke-ota/mrubyc_with_platformio.git
~~~

5. mrubyc_with_platformio/srcをsrcディレクトリに上書き

~~~pwsh
mv -r ./mrubyc_with_platformio/src ./src
rm -r ./mrubyc_with_platformio
~~~

6. lib/mrubyc/srcにあるhal_*ディレクトリの内、使用するボードに対応するものをhalにリネーム

~~~pwsh
REN ./lib/mrubyc/src/hal_you_use ./lib/mrubyc/src/hal
rm -r ./lib/mrubyc/src/hal_*
~~~

7. 作業フォルダ内でPlatformIOで開発環境の初期化

libディレクトリをいじった後は毎回行う

~~~pwsh
pio init --ide your_ide_id --board your_board_ide
~~~

### 作業手順

1. src内のmain.cppにrubyで使用したいメソッドを登録

~~~ cpp
// sample method
// When you write your method, write like this.
//
void c_sample_method(VM *VM, mrbc_value *v, int arg){
}
// 上の空関数を参考に、使用したい関数を実装

static void mrbc_define_methods(){
    mrbc_define_method(nullptr, mrbc_class_object, "sample_method", c_sample_method);
    // 上の関数を参考に、rubyで呼び出したいメソッドを登録
}
~~~

2. srcフォルダの中でRubyファイルを作成、編集

3. Rubyファイルをmrubyコンパイラでコンパイル

~~~pwsh
mrbc.exe -E -B your_file_name your_file_name.rb
~~~

4. コンパイル後の*.cコードをmain.cppから呼び出し

~~~cpp
#include "Arduino.h"
#include "mrubyc.h"

// 後ほどmrubyのコンパイラでコンパイルした.rbファイルの処理が格納される配列です。
extern const uint8_t your_file_name[];
~~~

5. PlatformIOでビルド、アップロード
