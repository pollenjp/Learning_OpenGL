# ch04 Programmable Shader - sample1

- [`point.vert`](#pointvert)
- [`point.frag`](#pointfrag)
- [Execute](#Execute)

```
$ make
```

## `point.vert`

---

```
#version 150 core
```

- GLSL のバージョン指定.
    - 150  : OpenGL 3.2 以降で使用できる GLSL のバージョン 1.5 を使用するということ
    - core : OpenGL 3.0 より前のバージョンの機能をサポートしない Core Profile を用いるということ

---

```
in vec4 position
```

- レンダリングパイプラインの前のステージからこのシェーダプログラムに送られたデータを受け取る in 変数をposition という変数名で宣言.
- バーテックスシェーダの in 変数には、CPU から送られた図形データの一つの頂点のデータが格納
- この頂点のデータを __頂点属性 (attribute)__ といい、この in 変数を特に __attribute変数__ という.


## point.frag

---

```
out vec4 fragment;
```

- フラグメントの色の出力先の out 変数を fragment という変数名で宣言.
- out 変数に代入したデータは, レンダリングパイプラインの次のステージに送られる.
- フラグメントシェーダの out 変数に代入した値は, フレームバッファのカラーバッファに格納さる.


## Execute

出力ウィンドウはch03と同じ

```
make
```

`main()`の中の以下の箇所は下２行をコメントアウトして上のコメントを外すとファイルから読み込まずシェーダプログラムを文字列として直接読み込むことになる.

```
  //// バーテックスシェーダのソースプログラム
  //static constexpr GLchar vsrc[] = "#version 150 core\n"
  //                                 "in vec4 position;\n"
  //                                 "void main()\n"
  //                                 "{\n"
  //                                 "  gl_Position = position;\n"
  //                                 "}\n";
  //// フラグメントシェーダのソースプログラム
  //static constexpr GLchar fsrc[] = "#version 150 core\n"
  //                                 "out vec4 fragment;\n"
  //                                 "void main()\n"
  //                                 "{\n"
  //                                 "  fragment = vec4(1.0, 0.0, 0.0, 1.0);\n"
  //                                 "}\n";
  //// プログラムオブジェクトを作成する
  //const GLuint program(createProgram(/* const char *vsrc= */ vsrc, /* const char *fsrc= */ fsrc));

  // プログラムオブジェクトを作成する
  const GLuint program(/* GLuint */loadProgram(/* const char *vertex_filename  = */ "point.vert",
                                               /* const char *fragment_filename= */ "point.frag"));
```
