#pragma once
#include <GL/glew.h>


// @brief class 図形データ
class Object
{
  // 頂点配列オブジェクト名
  GLuint vertex_array_object;
  // 頂点バッファオブジェクト名
  GLuint vertex_buffer_objext;


private:
  //========================================
  // > ○○くんのために一所懸命書いたものの結局○○くんの卒業に間に合わなかったGLFW による OpenGL 入門 - p79
  // > ただし,これだとインスタンスのコピーが複数作られたときに,そのうちのどれか一つを削除すると,
  // > それらの間で共有されている頂点配列オブジェクトや頂点バッファオブジェクトが削除されてしまいます.
  // > そうすると残りのインスタンスが使えなくなるほか,それらを削除しようとしたときに既に削除された
  // > バッファオブジェクトを削除しようとして,OpenGL のエラーを引き起こしてしまいます.
  // > そこでコピーコンストラクタと代入演算子を private メンバにして,インスタンスのコピーを禁止します
  // > (コピーしようとするとコンパイルエラーになります).
  // @ref: [C++ のコピーコンストラクターと代入演算子 | プログラマーズ雑記帳](http://yohshiy.blog.fc2.com/blog-entry-303.html)

  // @brief constructor コピーコンストラクタによるコピー禁止
  Object(const Object &o);
  // @brief constructor 代入によるコピー禁止
  Object &operator=(const Object &o);
  //========================================


public:
  // @brief struct, 頂点(x,y)の定義
  struct Vertex
  {
    // 頂点属性
    GLfloat position[2];  // (x,y)
  };

  // @brief constructor
  // @param (const GLint   dim_size     ) 頂点の位置の次元
  // @param (const GLsizei vertex_count ) 頂点の数
  // @param (const Vertex  *vertex_array) 頂点属性を格納した配列
  Object(const GLint   dim_size,
         const GLsizei vertex_count,
         const Vertex  *vertex_array)
  {
    // Vertex Array Object - 頂点配列オブジェクト
    // > [glGenVertexArrays - OpenGL 4 Reference Pages](https://www.khronos.org/registry/OpenGL-Refpages/gl4/html/glGenVertexArrays.xhtml)
    // > - n vertex array object names in arrays.
    // >   There is no guarantee that the names form a contiguous set of integers;
    // >   however, it is guaranteed that none of the returned names was in use immediately before the call to glGenVertexArrays.
    // > - The names returned in arrays are marked as used, for the purposes of glGenVertexArrays only, but they acquire state and type only when they are first bound.
    // つまり,使用可能な(まだ使われていない)頂点配列オブジェクト名(番号)をarraysに格納する.
    // 今回は n=1 なので vertex_array_object は配列ではなく GLuint で宣言されている.
    glGenVertexArrays(/* GLsizei n      = */ 1,                      // the number of vertex array object names to generate
                      /* GLuint  *arrays= */ &vertex_array_object);  // an array in which the generated vertex array object names (number) are stored
    // > [glBindVertexArray - OpenGL 4 Reference Pages](https://www.khronos.org/registry/OpenGL-Refpages/gl4/html/glBindVertexArray.xhtml)
    // > - binds the vertex array object with name array
    // > - array is the name of a vertex array object previously returned from a call to glGenVertexArrays,
    // >   or zero to break the existing vertex array object binding.
    // > - If the bind is successful no change is made to the state of the vertex array object, and any previous vertex array object binding is broken.
    // glGenVertexArrays頂点配列オブジェクト名(番号)と頂点配列オブジェクトを結ぶつける.
    glBindVertexArray(/* GLuint array= */ vertex_array_object);  // Specifies the name of the vertex array to bind.

    // Vertex Buffer Object 頂点バッファオブジェクト
    // > 頂点バッファオブジェクトを作成し,このデータをそこに送ります.
    // > 頂点バッファオブジェクトは GPU 側に確保したデータの保存領域を管理します.
    //
    // > [glGenBuffers - OpenGL 4 Reference Pages](https://www.khronos.org/registry/OpenGL-Refpages/gl4/html/glGenBuffers.xhtml)
    // glGenVertexArraysと似たような感じ
    glGenBuffers(/* GLsizei n      = */ 1,                       // Specifies the number of buffer object names to be generated.
                 /* GLuint *buffers= */ &vertex_buffer_objext);  // Specifies an array in which the generated buffer object names are stored.
    // [glBindBuffer - OpenGL 4 Reference Pages](https://www.khronos.org/registry/OpenGL-Refpages/gl4/html/glBindBuffer.xhtml)
    glBindBuffer(/* GLenum target= */ GL_ARRAY_BUFFER,        // Purpose : Vertex attributes
                 /* GLuint buffer= */ vertex_buffer_objext);
    // [glBufferData - OpenGL 4 Reference Pages](https://www.khronos.org/registry/OpenGL-Refpages/gl4/html/glBufferData.xhtml)
    glBufferData(/* GLenum       target= */ GL_ARRAY_BUFFER,  // Purpose : Vertex attributes
                 /* GLsizeiptr   size  = */ vertex_count * sizeof(Vertex),
                 /* const GLvoid *data = */ vertex_array,
                 /* GLenum       usage = */ GL_STATIC_DRAW);  // Specifies the expected usage pattern of the data store.

    // 結合されている頂点バッファオブジェクトを in 変数から参照できるようにする
    // > ○○くんのために一所懸命書いたものの結局○○くんの卒業に間に合わなかったGLFW による OpenGL 入門 - p76
    // > - index : シェーダプログラムのリンク時に glBindAttribLocation() 関数で指定した, データを受け取る attribute 変数の場所.
    // >           このシェーダプログラムでは vertex の唯一のメンバ position の index に 0 を指定していますから、ここでは 0 を指定しています。
    // > [glVertexAttribPointer - OpenGL 4 Reference Pages](https://www.khronos.org/registry/OpenGL-Refpages/gl4/html/glVertexAttribPointer.xhtml)
    // > - Specifies the byte offset between consecutive generic vertex attributes. If stride is 0, the generic vertex attributes are understood to be tightly packed in the array. 
    glVertexAttribPointer(/* GLuint       index     = */ 0,         // シェーダプログラムのリンク時に glBindAttribLocation() 関数で指定した, データを受け取る attribute 変数の場所
                          /* GLint        size      = */ dim_size,  // Specifies the number of components per generic vertex attribute. Must be 1, 2, 3, 4.
                          /* GLenum       type      = */ GL_FLOAT,
                          /* GLboolean    normalized= */ GL_FALSE,
                          /* GLsizei      stride    = */ 0,         // 0 ならデータは密に並んでいるものとして扱う
                          /* const GLvoid *pointer  = */ 0);        // attribute 変数が受け取るデータが格納されている場所. 頂点バッファオブジェクトの先頭から取り出すならを指定.

    // [glEnableVertexAttribArray - OpenGL 4 Reference Pages](https://www.khronos.org/registry/OpenGL-Refpages/gl4/html/glEnableVertexAttribArray.xhtml)
    glEnableVertexAttribArray(/* GLuint index= */ 0);  // 有効にする attribute 変数の場所
  }

  // @brief destructor
  // @ref [C++の基礎 : コンストラクタ/デストラクタ](https://www.s-cradle.com/developer/sophiaframework/tutorial/Cpp/ctordtor.html)
  virtual ~Object()
  {
    // 頂点配列オブジェクトを削除する
    glDeleteBuffers(/* GLsizei      n       = */ 1, /* const GLuint *buffers= */ &vertex_array_object);
    // 頂点バッファオブジェクトを削除する
    glDeleteBuffers(/* GLsizei      n       = */ 1, /* const GLuint *buffers= */ &vertex_buffer_objext);
  }

  void bind() const
  // 頂点配列オブジェクトの結合
  // > ○○くんのために一所懸命書いたものの結局○○くんの卒業に間に合わなかったGLFW による OpenGL 入門 - p79
  // > 図形を描画するときは,あらかじめ glBindVertexArray() により頂点配列オブジェクトを結合しておく必要があるので,この処理を行うメソッド bind() を用意しておきま
  {
    // 描画する頂点配列オブジェクトを指定する
    glBindVertexArray(/* GLuint array= */ vertex_array_object);
  }

};
