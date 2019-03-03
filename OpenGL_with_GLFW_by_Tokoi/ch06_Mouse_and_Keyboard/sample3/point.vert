#version 150 core
// GLSL のバージョン指定.
// 150  : OpenGL 3.2 以降で使用できる GLSL のバージョン 1.5 を使用するということ.
// core : OpenGL 3.0 より前のバージョンの機能をサポートしない Core Profile を用いるということ.

// uniform 変数は一回の描画命令で使用される全ての頂点から共通して参照される値を保持
uniform vec2 size;
uniform float scale;

// レンダリングパイプラインの前のステージからこのシェーダプログラムに送られたデータを受け取る in 変数をposition という変数名で宣言.
// バーテックスシェーダの in 変数には, CPU から送られた図形データの一つの頂点のデータが格納される.
// この頂点のデータを頂点属性 (attribute) といい、この in 変数を特に attribute変数 という.
in vec4 position;

void main()
{
  // gl_Position は GLSL の組み込み変数で,この変数に代入した値がパイプラインの次のステージに送られる.
  // バーテックスシェーダは必ずこの変数 (gl_Position) に値を代入
  // X 座標値だけを 1 / aspect 倍
  gl_Position = vec4(2.0 * scale / size, 1.0, 1.0) * position;
}

