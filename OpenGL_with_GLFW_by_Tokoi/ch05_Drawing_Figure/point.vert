#version 150 core
// GLSL のバージョン指定.
// 150  : OpenGL 3.2 以降で使用できる GLSL のバージョン 1.5 を使用するということ.
// core : OpenGL 3.0 より前のバージョンの機能をサポートしない Core Profile を用いるということ.

in vec4 position;
// レンダリングパイプラインの前のステージからこのシェーダプログラムに送られたデータを受け取る in 変数をposition という変数名で宣言.
// バーテックスシェーダの in 変数には, CPU から送られた図形データの一つの頂点のデータが格納される.
// この頂点のデータを頂点属性 (attribute) といい、この in 変数を特に attribute変数 という.

void main()
{
  // gl_Position は GLSL の組み込み変数で,この変数に代入した値がパイプラインの次のステージに送られる.
  // バーテックスシェーダは必ずこの変数に値を代入
  gl_Position = position;
}

