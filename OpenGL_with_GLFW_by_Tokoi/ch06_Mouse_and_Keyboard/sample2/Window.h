#pragma once
#include <iostream>
#include <GL/glew.h>
#include <GLFW/glfw3.h>

// ウィンドウ関連の処理
class Window
{
private:
  // ウィンドウのハンドル
  GLFWwindow *const window;
  // 縦横比
  GLfloat aspect;

public:
  // @brief constructor
  // @param (int          width ) window width
  // @param (int          height) window height
  // @param (const char * title ) title string
  Window(int        width  = 640,
         int        height = 480,
         const char *title = "Hello!"):
         // create window
         window(/* LFWwindow * */glfwCreateWindow(/* int         width   = */ width,
                                                  /* int         height  = */ height,
                                                  /* const char  *title  = */ title,
                                                  /* GLFWmonitor *monitor= */ NULL,
                                                  /* GLFWwindow  *share  = */ NULL))
  {
    if (window == NULL){  // if you fail in creating a window (ウィンドウ作成に失敗した処理)
      std::cerr << "Can't create GLFW window." << std::endl;
      exit(1);  // interupt
    }
    std::cout << "Created GLFW window!" << std::endl;

    // 作成したウィンドウを現在のウィンドウ(処理対象)とする
    glfwMakeContextCurrent(/* GLFWwindow *window= */ window);
    std::cout << "Set the window as the current!" << std::endl;

    // GLEW を初期化する (Initialize GLEW)
    glewExperimental = GL_TRUE;
    if (glewInit() != GLEW_OK)
    {
      // GLEW の初期化に失敗した
      std::cerr << "Can't initialize GLEW" << std::endl;
      exit(1);  // interupt
    }
    std::cerr << "Initialized GLEW" << std::endl;

    // 垂直同期のタイミングを待つように設定する
    // カラーバッファを入れ替える際に待つディスプレイの垂直同期タイミング (V-Sync) の最小回数
    glfwSwapInterval(/* int interval= */1);

    // @brief このインスタンスの this ポインタを記録しておく
    // @detail
    //   > ○○くんのために一所懸命書いたものの結局○○くんの卒業に間に合わなかったGLFW による OpenGL 入門 - p92
    //     静的メンバ関数はインスタンスを生成していない (すなわち,メンバ変数にメモリが割り当てられていない) ときにも
    //     呼び出せるかわりに,その中でメンバ変数を参照することができません. 静的メンバ関数内でメンバ変数を参照する
    //     ためには,そのインスタンスの実体 (割り当てられたメモリ) の場所を知る必要があります.
    //   > [glfwSetWindowUserPointer() - GLFW: Window reference](https://www.glfw.org/docs/latest/group__window.html#ga3d2fc6026e690ab31a13f78bc9fd3651)
    glfwSetWindowUserPointer(/* GLFWwindow * window = */ window, /* void * pointer= */ this);

    // ウィンドウのサイズ変更時に呼び出す処理を設定
    // @detail
    //   > ○○くんのために一所懸命書いたものの結局○○くんの卒業に間に合わなかったGLFW による OpenGL 入門 - p89
    //     引数 cbfun に設定する関数は次の形式で定義します. ここでは関数名を resize() とします
    //     @param (GLFWwindow *const window) サイズが変更されたウィンドウのハンドル
    //     @param (int width)                それぞれサイズ変更後のウィンドウのwidth
    //     @param (int height)               それぞれサイズ変更後のウィンドウのheight
    //   > ○○くんのために一所懸命書いたものの結局○○くんの卒業に間に合わなかったGLFW による OpenGL 入門 - p90
    //     メンバ関数をコールバック関数に使う場合は、静的メンバ関数である必要があります
    //   > [glfwSetWindowSizeCallback() - GLFW: Window reference](https://www.glfw.org/docs/latest/group__window.html#gaa40cd24840daa8c62f36cafc847c72b6)
    glfwSetWindowSizeCallback(/* GLFWwindow *const window= */window, /* GLFWwindowsizefun cbfun= */resize);
    // 開いたウィンドウの初期設定
    resize(window, width, height);
  }

  // @brief destructor
  virtual ~Window()
  {
    // 指定されたウィンドウとそのコンテキストを破棄
    // > [GLFW: Window reference](https://www.glfw.org/docs/latest/group__window.html#gacdf43e51376051d2c091662e9fe3d7b2)
    glfwDestroyWindow(/* GLFWwindow *window= */window);
  }

  // @brief accessor 縦横比を取り出す
  GLfloat getAspect() const { return aspect; }

  // @brief method ウィンドウのサイズ変更時の処理
  // @param (GLFWwindow *const window) ウィンドウ
  // @param (int width)                ウィンドウの横幅
  // @param (int height)               ウィンドウの高さ
  // @detail
  //   This function is called by glfwSetWindowSizeCallback() in this constructor as a callback function.
  //   This callback should be a static menber.
  //   > ○○くんのために一所懸命書いたものの結局○○くんの卒業に間に合わなかったGLFW による OpenGL 入門 - p89
  //     引数 cbfun に設定する関数は次の形式で定義します. ここでは関数名を resize() とします
  //     @param (GLFWwindow *const window) サイズが変更されたウィンドウのハンドル
  //     @param (int width)                それぞれサイズ変更後のウィンドウのwidth
  //     @param (int height)               それぞれサイズ変更後のウィンドウのheight
  //   > ○○くんのために一所懸命書いたものの結局○○くんの卒業に間に合わなかったGLFW による OpenGL 入門 - p90
  //     メンバ関数をコールバック関数に使う場合は、静的メンバ関数である必要があります
  static void resize(GLFWwindow *const window, int width, int height)
  {
    // ウィンドウ全体をビューポートに設定する
    // [glViewport](https://www.khronos.org/registry/OpenGL-Refpages/es2.0/xhtml/glViewport.xml)
    glViewport(/* GLint   x     = */ 0,
               /* GLint   y     = */ 0,
               /* GLsizei width = */ width,
               /* GLsizei height= */ height);

    // このインスタンスの this ポインタを得る
    Window * const instance(static_cast<Window *>(/* void * */glfwGetWindowUserPointer(/* GLFWwindow * 	window= */window)));

    if (instance != NULL)
    {
      std::cout << "Update aspect!" << std::endl;
      // このインスタンスが保持する縦横比を更新する (update aspect)
      instance->aspect = static_cast<GLfloat>(width) / static_cast<GLfloat>(height);
    } else {  // if instace is null pointer
      std::cerr << "`instance` variable in Window.resize() is NULL (null pointer)." << std::endl;
    }

  }

  // @brief method ウィンドウを閉じるべきかを判定する
  int shouldClose() const
  {
    return glfwWindowShouldClose(/* GLFWwindow *window= */window);
  }

  // @brief method カラーバッファを入れ替えてイベントを取り出す.
  // @detail ダブルバッファリング
  void swapBuffers()
  {
    // カラーバッファ入れ替え <= ダブルバッファリング
    glfwSwapBuffers(/* GLFWwindow *window= */window);
    // イベントを取り出す (ポーリング方式)
    glfwWaitEvents();
  }

};
