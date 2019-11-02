#include "Arduino.h"
#include "mrubyc.h"

// 後ほどmrubyのコンパイラでコンパイルした.rbファイルの処理が格納される配列です。
extern const uint8_t task1[];
extern const uint8_t task2[];

// for esp32
#define MEMORY_SIZE (1024*30)
static uint8_t memory_pool[MEMORY_SIZE];

// ruby側で使用したいメソッドを実装します。
// 基本形は以下の通りです。
// 引数を取る場合は第1引数v[1],第2引数v[2]であることに注意してコーディングします。
// 第1引数に整数を使用する場合 int value_name = GET_INT_ARG(1);
// 第2引数に浮動小数を使用する場合 float value_name = GET_FLOAT_ARG(2);
void c_sample_method(VM *VM, mrbc_value *v, int arg){
}
void c_Serial_println(VM *VM, mrbc_value *v, int arg){
    uint8_t *character_array = GET_STRING_ARG(1);
    String str = String((char *)character_array);
    Serial.println(str);
}

// 実装したメソッドを登録します。
// 基本形はmrbc_define_method( nullptr, mrbc_class_object, "Rubyで使いたいメソッド名", メソッドの実装);
static void mrbc_define_methods(){
    mrbc_define_method( nullptr, mrbc_class_object, "sample_method", c_sample_method);
    mrbc_define_method( nullptr, mrbc_class_object, "Serial_print", c_Serial_println);
}

void setup() {
//  replace Serial.begin( here! )
//  ex) esp32 can use  Serial.begin(115200)
    Serial.begin(9600);

    delay(1000);

    // initialize mruby/c
    Serial.println("--- begin setup");
    mrbc_init(memory_pool, MEMORY_SIZE);
    mrbc_define_methods();

    // マルチタスクを行いたい場合は以下のように追加してください
    // 基本形 mrbc_create_task(5行目あたりで宣言した配列, nullptr);
    mrbc_create_task(task1, nullptr);
    mrbc_create_task(task2, nullptr);

    Serial.println("--- run mruby script");

    // mruby/cのVMを動かします
    // なお、内部は無限ループとなっているため、これ以降のコードにはたどり着けません。
     mrbc_run();
}

void loop() {
    // setup()が終わらないためたどり着けない。
}
