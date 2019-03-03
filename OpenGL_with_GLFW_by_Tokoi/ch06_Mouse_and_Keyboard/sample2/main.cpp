/**
 * @file main.cpp
 * @brief main program
 * @author pollenjp
 * @date
 * @detail
 *   - [◯◯くんのために一所懸命書いたものの結局◯◯くんの卒業に間に合わなかった GLFW による OpenGL 入門 (draft 版) - 和歌山大学システム工学部 床井浩平](http://marina.sys.wakayama-u.ac.jp/~tokoi/GLFWdraft.pdf)
 */
#include <cstdlib>
#include <iostream>
#include <fstream>
#include <vector>
#include <memory>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "Window.h"
#include "Shape.h"

// @brief シェーダオブジェクトのコンパイル結果を表示する
// @param (GLuint       shader) シェーダオブジェクト名
// @param (const char * str   ) コンパイルエラーが発生した場所を示す文字列
// @return (GLboolean   -     ) error status boolean
GLboolean printShaderInfoLog(GLuint shader, const char *str)
{
  // コンパイル結果を取得する
  // [glGetShader - OpenGL 4 Reference Pages](https://www.khronos.org/registry/OpenGL-Refpages/gl4/html/glGetShader.xhtml)
  GLint status;
  glGetShaderiv(/* GLuint shader = */ shader,             // 情報を取り出すシェーダオブジェクト
                /* GLenum pname  = */ GL_COMPILE_STATUS,  // shader に指定したシェーダオブジェクトのコンパイルが成功したかどうか (GL_TRUE or GL_FALSE)
                /* GLint  *params= */ &status);           // 取り出した情報の格納先
  if (!status) std::cerr << "Compile Error in " << str << std::endl;

  // シェーダのコンパイル時のログの長さを取得する
  GLsizei bufSize;  // GLsizei : 32 bitdepth. A non-negative binary integer, for sizes.
  glGetShaderiv(/* GLuint shader = */ shader,              // 情報を取り出すシェーダオブジェクト
                /* GLenum pname  = */ GL_INFO_LOG_LENGTH,  // コンパイル時に生成されたログの長さを調べて *params に格納
                                                           // ログがなければ 0 を格納
                /* GLint  *params= */ &bufSize);           // 取り出した情報の格納先
  if (bufSize > 1){
    // シェーダのコンパイル時のログの内容を取得する
    std::vector<GLchar> infoLog(/* GLsizei */ bufSize);  // 書記要素数が bufSize の動的配列 infoLog
                                                         // charの配列なのでstringと思えば良い
    GLsizei length;
    glGetShaderInfoLog(/* GLuint  shader   = */ shader,
                       /* GLsizei maxLength= */ bufSize,
                       /* GLsizei *length  = */ &length,
                       /* GLchar  *infoLog = */ &infoLog[0]);
    std::cerr << &infoLog[0] << std::endl;
  }

  return static_cast<GLboolean>(/* GLint */status);  // GLint => GLboolean
}


// @brief プログラムオブジェクトのリンク結果を表示する
// @param (GLuint program) プログラムオブジェクト名
// @return (GLboolean -) error status boolean
GLboolean printProgramInfoLog(GLuint program)
{
  // リンク結果を取得する
  GLint status;
  glGetProgramiv(/* GLuint program= */ program,         // 情報を取り出すプログラムオブジェクト
                 /* GLenum pname  = */ GL_LINK_STATUS,  // params returns GL_TRUE if the last link operation on program was successful, and GL_FALSE otherwise
                 /* GLint  *params= */ &status);        // 取り出した情報の格納先
  if (status == GL_FALSE) std::cerr << "Link Error." << std::endl;
  // シェーダのリンク時のログの長さを取得する
  GLsizei bufSize;
  glGetProgramiv(program, GL_INFO_LOG_LENGTH, &bufSize);
  glGetProgramiv(/* GLuint program= */ program,             // 情報を取り出すプログラムオブジェクト
                 /* GLenum pname  = */ GL_INFO_LOG_LENGTH,  // params returns the number of characters in the information log for program
                                                            // including the null termination character (i.e., the size of the character buffer required to store the information log).
                                                            // If program has no information log, a value of 0 is returned.
                 /* GLint  *params= */ &bufSize);           // 取り出した情報の格納先
  if (/* GLsizei */ bufSize > 1)
  {
    // シェーダのリンク時のログの内容を取得する
    std::vector<GLchar> infoLog(bufSize);
    GLsizei length;
    glGetProgramInfoLog(/* GLuint  program  = */ program,
                        /* GLsizei maxLength= */ bufSize,
                        /* GLsizei *length  = */ &length,
                        /* GLchar  *infoLog = */ &infoLog[0]);
    std::cerr << &infoLog[0] << std::endl;
  }
  return static_cast<GLboolean>(/* GLint */status);  // GLint => GLboolean
}


// @brief プログラムオブジェクトを作成する
// @detail Create a Vertex Shader Object and a Fragment Shader Object. Read from source program.
// @param (const char * vsrc) バーテックスシェーダのソースプログラムの文字列
// @param (const char * fsrc) フラグメントシェーダのソースプログラムの文字列
// @return (GLuint program) プログラムオブジェクトの番号. If error, return 0.
// @ref [C++の基礎 : const 修飾子](https://www.s-cradle.com/developer/sophiaframework/tutorial/Cpp/const.html)
GLuint createProgram(const char *vsrc,
                     const char *fsrc)
{
  // 空のプログラムオブジェクトを作成する
  //   [glCreateProgram - OpenGL 4 Reference Pages](https://www.khronos.org/registry/OpenGL-Refpages/gl4/html/glCreateProgram.xhtml)
  std::cout << "Call glCreateProgram()." << std::endl;
  const GLuint program(/* GLuint */glCreateProgram());
  if(!program){  // 失敗した時の処理
    std::cerr << "Can't create an OpenGL Program Object." << std::endl;
  } else {
    std::cout << "Create an OpenGL Program Object." << std::endl;
  }

  if (vsrc != NULL){  // Vertex Shader
    // バーテックスシェーダのシェーダオブジェクトを作成する
    //   [glCreateShader - OpenGL 4 Reference Pages](https://www.khronos.org/registry/OpenGL-Refpages/gl4/html/glCreateShader.xhtml)
    const GLuint vobj(/* GLuint */ glCreateShader(/* GLenum shaderType= */ GL_VERTEX_SHADER));  
    if(!/* const GLuint */vobj){
      std::cerr << "Can't create an OpenGL Shader Object." << std::endl;
    } else {
      std::cout << "Create an OpenGL Shader Object." << std::endl;
    }
    // [glShaderSource - OpenGL 4 Reference Pages](https://www.khronos.org/registry/OpenGL-Refpages/gl4/html/glShaderSource.xhtml)
    glShaderSource(/*       GLuint  shader  = */ vobj,   // the handle of the shader object
                   /*       GLsizei count   = */ 1,      // the number of elements in the string and length arrays
                   /* const GLchar  **string= */ &vsrc,  // Specifies an array of pointers to strings containing the source code to be loaded into the shader
                   /* const GLint   *length = */ NULL);  // an array of string lengths
    glCompileShader(/* GLuint shader= */ vobj);

    // バーテックスシェーダのシェーダオブジェクトをプログラムオブジェクトに組み込む
    if(printShaderInfoLog(/* GLuint shader= */ vobj, /* const char *str= */ "vertex shader"))  // エラーが出ればstderrが起こる
      glAttachShader(/* GLuint program= */ program, /* GLuint shader= */ vobj);
    glDeleteShader(/* GLuint shader= */ vobj);
  }

  if (fsrc != NULL){  // Fragment Shader
    // フラグメントシェーダのシェーダオブジェクトを作成する
    const GLuint fobj(glCreateShader(/* GLenum shaderType= */ GL_FRAGMENT_SHADER));
    if(!fobj){
      std::cerr << "Can't create an OpenGL Shader Object." << std::endl;
    }
    glShaderSource(/*       GLuint  shader  = */ fobj,
                   /*       GLsizei count   = */ 1,
                   /* const GLchar  **string= */ &fsrc,
                   /* const GLint   *length = */ NULL);
    glCompileShader(/* GLuint shader= */ fobj);

    // フラグメントシェーダのシェーダオブジェクトをプログラムオブジェクトに組み込む
    if(printShaderInfoLog(/* GLuint shader= */ fobj, /* const char *str= */ "fragment shader"))  // エラーが出ればstderr
      glAttachShader(/* GLuint program= */ program, /* GLuint shader= */ fobj);
    glDeleteShader(/* GLuint shader= */ fobj);
  }

  // 図形の頂点の位置を受け取る attribute 変数 (変数名 position) の場所 (index) と
  // フラグメントシェーダから出力するデータを格納する変数 (変数名 fragment) の出力先 (colorNumber) を指定.
  // [glBindAttribLocation - OpenGL 4 Reference Pages](https://www.khronos.org/registry/OpenGL-Refpages/gl4/html/glBindAttribLocation.xhtml)
  glBindAttribLocation(/*       GLuint program= */ program,      // attribute 変数の場所を調べるプログラムオブジェクト名 (番号)
                       /*       GLuint index  = */ 0,            // 引数 name に指定した attribute 変数の場所を示す 0 以上の整数
                       /* const GLchar *name  = */ "position");  // バーテックスシェーダのソースプログラム中の attribute 変数の変数名の文字列
  // [glBindFragDataLocation - OpenGL 4 Reference Pages](https://www.khronos.org/registry/OpenGL-Refpages/gl4/html/glBindFragDataLocation.xhtml)
  glBindFragDataLocation(/*       GLuint program    = */ program,     // フラグメントの出力変数 (out 変数) の場所を調べるプログラムオブジェクト名 (番号)
                         /*       GLuint colorNumber= */ 0,           // 引数 name に指定した out 変数の場所 (番号) を,0 以上の整数で指定. 0 は標準のフレームバッファのカラーバッファを示す.
                         /* const char   *name      = */ "fragment"); // フラグメントシェーダのソースプログラム中の out 変数の変数名の文字列
  // プログラムオブジェクトをリンクする
  glLinkProgram(/* GLuint program= */ program);

  // 作成したプログラムオブジェクトを返す
  if(printProgramInfoLog(/* GLuint program= */ program))
    return /* GLuint program= */ program;

  glDeleteProgram(program);
  return 0;
}


// @brief シェーダのソースファイルを読み込んだメモリを返す
// @param (const char filename) シェーダのソースファイル名
// @param (const char buffer) 読み込んだソースファイルのテキストを書きこむ
// @return (bool -) return true if successfully read file.
bool readShaderSource(const char *filename, std::vector<GLchar> &buffer)
{
  if (filename == NULL) return false;
  std::ifstream file(/* const char* __s= */ filename, /* ios_base::openmode __mode= */ std::ios::binary);
  if (/* bool */file.fail())
  {
    std::cerr << "Error: Can't open source file: " << filename << std::endl;
    return false;
  }
  // ファイルの末尾に移動し現在位置(=ファイルサイズ)を得る
  // seekg : シーク操作(ポインタ移動)
  //    最初の引数(offset)に基準位置からのオフセット(Byte),二番目の引数(dir)に基準位置をセット
  //    ios_base::beg ファイルの先頭位置
  //    ios_base::cur 現在位置
  //    ios_base::end ファイルの最終位置
  file.seekg(/* streamoff offset= */ 0L, /* ios_base::seekdir dir= */ std::ios::end);
  // ファイルサイズのメモリを確保
  GLsizei length = static_cast<GLsizei>(/* pos_type */file.tellg());
  buffer.resize(/* size_type n= */length + 1);
  // ファイルを先頭から読み込む
  file.seekg(/* streamoff offset= */ 0L, /* ios_base::seekdir dir= */ std::ios::beg);
  file.read(/* char* s= */buffer.data(), /* streamsize n= */length);
  buffer[length] = '\n';
  if (file.fail())
  {
    // うまく読み込めなかった
    std::cerr << "Error: Could not read souce file: " << filename << std::endl;
    file.close();
    return false;
  }
  // 読み込み成功
  file.close();
  return true;
}


// @brief シェーダのソースファイルを読み込んでプログラムオブジェクトを作成する
// @param (const char * vertex_filename) バーテックスシェーダのソースファイル名
// @param (const char * fragment_filename) フラグメントシェーダのソースファイル名
// @return (GLuint -) return program object index if successfully read file, 0 otherwise.
GLuint loadProgram(const char *vertex_filename, const char *fragment_filename)
{
  // シェーダのソースファイルを読み込む
  // Vertex
  std::vector<GLchar> vertex_shader_src;
  const bool v_status(/* bool */readShaderSource(/* const char          *filename= */ vertex_filename,
                                                 /* std::vector<GLchar> &buffer  = */ vertex_shader_src));
  if (!v_status){
    std::cerr << "Failed to read Vertex Sahder Source" << std::endl;
  } else {
    std::cout << "Success to read Vertex Sahder Source" << std::endl;
  }

  // Fragment
  std::vector<GLchar> fragment_shader_src;
  const bool f_status(/* bool */readShaderSource(/* const char          *filename= */ fragment_filename,
                                                 /* std::vector<GLchar> &buffer  = */ fragment_shader_src));
  if (!f_status){
    std::cerr << "Failed to read Fragment Sahder Source" << std::endl;
  } else {
    std::cout << "Success to read Fragment Sahder Source" << std::endl;
  }

  // プログラムオブジェクトを作成する
  return v_status && f_status ? /* GLuint */ createProgram(/* const char *vsrc= */vertex_shader_src.data(),
                                                           /* const char *fsrc= */fragment_shader_src.data()) : 0;
}


// 矩形の頂点の位置
// > [constexpr - cpprefjp C++日本語リファレンス](https://cpprefjp.github.io/lang/cpp11/constexpr.html)
// > constexprは、汎用的に定数式を表現するための機能である.
// > この機能を使用することで,コンパイル時に値が決定する定数,コンパイル時に実行される関数,コンパイル時にリテラルとして振る舞うクラスを定義できる.
constexpr Object::Vertex rectangle_vertex[] = {{-0.5f, -0.5f},
                                               { 0.5f, -0.5f},
                                               { 0.5f,  0.5f},
                                               {-0.5f,  0.5f}};


int main()
{
  // GLFW の初期化 (GLFW)
  if (!/* int */glfwInit()){  // 初期化に失敗した処理
    std::cerr << "Can't initialize GLFW" << std::endl;
    return 1;
  }
  std::cout << "Initialized GLFW!" << std::endl;


  // 終了時の処理登録
  std::atexit(/* *func= */ glfwTerminate);  // [std::atexit - cppreference.com](https://en.cppreference.com/w/cpp/utility/program/atexit)

  // OpenGL Version 3.2 Core Profile を選択する
  std::cout << "Giving hint to glfw window..." << std::endl;
  glfwWindowHint(/* hint= */GLFW_CONTEXT_VERSION_MAJOR, /* int value=*/3);
  glfwWindowHint(/* hint= */GLFW_CONTEXT_VERSION_MINOR, /* int value=*/2);
  glfwWindowHint(/* hint= */GLFW_OPENGL_FORWARD_COMPAT, /* int value=*/GL_TRUE);
  glfwWindowHint(/* hint= */GLFW_OPENGL_PROFILE,        /* int value=*/GLFW_OPENGL_CORE_PROFILE);

  // ウィンドウを作成する
  Window window;

  // 現在のウィンドウの背景色を設定 (background color)
  glClearColor(/* GLfloat red   = */ 1.0f,
               /* GLfloat green = */ 1.0f,
               /* GLfloat blue  = */ 1.0f,
               /* GLfloat alpha = */ 0.0f);

  // プログラムオブジェクトを作成する
  const GLuint program(/* GLuint */loadProgram(/* const char *vertex_filename  = */ "point.vert",
                                               /* const char *fragment_filename= */ "point.frag"));
  if (!program){
    std::cout << "Failed to Load vertex and fragment program and Create Program Object." << std::endl;
  }

  // 図形データを作成する
  // > ○○くんのために一所懸命書いたものの結局○○くんの卒業に間に合わなかったGLFW による OpenGL 入門 - p82
  // > 図形の描画は Shape クラスのインスタンスを生成して行いますが, そのポインタをスマート
  // > ポインタ unique_ptr にします. unique_ptr は shared_ptr と違って複数のポインタが同じインスタ
  // > ンスを指すことはありませんが,ポインタが削除されたときに,それが指すインスタンスも自動
  // > 的に削除 (delete) してくれます. これを使うために, ここでも memory を #include します。
  std::unique_ptr<const Shape> shape(new Shape(/*       GLint          dim_size,    = */ 2,
                                               /*       GLsizei        vertex_count = */ 4,
                                               /* const Object::Vertex *vertex_array= */ rectangle_vertex));

  // ループ処理
  // window が開いている間繰り返す
  int i = 0;
  while (!window.shouldClose()){
    std::cout << "While Loop : " << i << std::endl;
    i++;

    // ウィンドウを消去
    glClear(/* GLbitfield mask= */ GL_COLOR_BUFFER_BIT);  // glClear : https://www.khronos.org/registry/OpenGL-Refpages/es2.0/xhtml/glClear.xml

    // シェーダプログラムの使用開始
    // glUseProgram(program); は,使用するシェーダプログラムが一つしかなければ,while ループの前に置くことができる.
    // シェーダプログラムを描画命令のたびに切り替えて使う場合は,この62while ループの中に置いてください.
    // なお,シェーダプログラムが不要になれば glUseProgram(0); を実行するが,シェーダプログラムは使いっぱなしでも構わない.
    glUseProgram(/* GLuint program= */ program);

    // 図形を描画する
    shape->draw();

    // カラーバッファを入れ替えてイベントを取り出す
    window.swapBuffers();
  }

  return 0;
}
