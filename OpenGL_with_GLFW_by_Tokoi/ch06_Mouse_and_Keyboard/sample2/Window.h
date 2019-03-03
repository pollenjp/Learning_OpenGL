#pragma once
#include <iostream>
#include <GL/glew.h>
#include <GLFW/glfw3.h>

// ウィンドウ関連の処理
class Window
{
  // ウィンドウのハンドル
  GLFWwindow *const window;

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

    // ウィンドウのサイズ変更時に呼び出す処理を設定
    // > ○○くんのために一所懸命書いたものの結局○○くんの卒業に間に合わなかったGLFW による OpenGL 入門 - p89
    //   引数 cbfun に設定する関数は次の形式で定義します. ここでは関数名を resize() とします
    //   @param (GLFWwindow *const window) サイズが変更されたウィンドウのハンドル
    //   @param (int width)                それぞれサイズ変更後のウィンドウのwidth
    //   @param (int height)               それぞれサイズ変更後のウィンドウのheight
    // > ○○くんのために一所懸命書いたものの結局○○くんの卒業に間に合わなかったGLFW による OpenGL 入門 - p90
    //   メンバ関数をコールバック関数に使う場合は、静的メンバ関数である必要があります
    // > [glfwSetWindowSizeCallback() - GLFW: Window reference](https://www.glfw.org/docs/latest/group__window.html#gaa40cd24840daa8c62f36cafc847c72b6)
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

  // @brief method ウィンドウのサイズ変更時の処理
  // @param (GLFWwindow *const window) ウィンドウ
  // @param (int width)                ウィンドウの横幅
  // @param (int height)               ウィンドウの高さ
  // 
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
  }
};