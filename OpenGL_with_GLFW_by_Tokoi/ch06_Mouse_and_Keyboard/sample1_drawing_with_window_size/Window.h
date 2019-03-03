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
  /**
   * 
   */
  Window(int        width  = 640,
         int        height = 480,
         const char *title = "Hello!")
         : window(/* LFWwindow * */glfwCreateWindow(/* int          width  = */ width,
                                                    /* int          height = */ height,
                                                    /* const char  *title  = */ title,
                                                    /* GLFWmonitor *monitor= */ NULL,
                                                    /* GLFWwindow  *share  = */ NULL))
  {
    if (window == NULL){ // ウィンドウ作成に失敗した処理
      std::cerr << "Can't create GLFW window." << std::endl;
      exit(1);
    }
    std::cout << "Created GLFW window!" << std::endl;

    // 作成したウィンドウを現在のウィンドウ(処理対象)とする
    glfwMakeContextCurrent(/* GLFWwindow *window= */ window);
    std::cout << "Set the window as the current!" << std::endl;

    // GLEW を初期化する
    glewExperimental = GL_TRUE;
    if (glewInit() != GLEW_OK)
    {
      // GLEW の初期化に失敗した
      std::cerr << "Can't initialize GLEW" << std::endl;
      exit(1);
    }
    std::cerr << "Initialized GLEW" << std::endl;

    // 垂直同期のタイミングを待つ
    // カラーバッファを入れ替える際に待つディスプレイの垂直同期タイミング (V-Sync) の最小回数
    glfwSwapInterval(/* int interval= */1);

    // ウィンドウのサイズ変更時に呼び出す処理の登録
    glfwSetWindowSizeCallback(/* GLFWwindow *const window= */window, /* GLFWwindowsizefun cbfun= */resize);
    // 開いたウィンドウの初期設定
    resize(window, width, height);
  }

  virtual ~Window()
  {
    // 指定されたウィンドウとそのコンテキストを破棄
    // > [GLFW: Window reference](https://www.glfw.org/docs/latest/group__window.html#gacdf43e51376051d2c091662e9fe3d7b2)
    glfwDestroyWindow(/* GLFWwindow *window= */window);
  }

  /**
   * ウィンドウを閉じるべきかを判定する
   */
  int shouldClose() const
  {
    return glfwWindowShouldClose(/* GLFWwindow *window= */window);
  }

  /**
   * カラーバッファを入れ替えてイベントを取り出す
   * ダブルバッファリング
   */
  void swapBuffers()
  {
    // カラーバッファ入れ替え <= ダブルバッファリング
    glfwSwapBuffers(/* GLFWwindow *window= */window);
    // イベントを取り出す (ポーリング方式)
    glfwWaitEvents();
  }

  // ウィンドウのサイズ変更時の処理
  /**
   * @param (GLFWwindow *const window) | ウィンドウ
   * @param (int width)                | ウィンドウの横幅
   * @param (int height)               | ウィンドウの高さ
   */
  static void resize(GLFWwindow *const window, int width, int height)
  {
    // ウィンドウ全体をビューポートに設定する
    glViewport(0, 0, width, height);
    // [glViewport](https://www.khronos.org/registry/OpenGL-Refpages/es2.0/xhtml/glViewport.xml)
    glViewport(/* GLint   x     = */ 0,
               /* GLint   y     = */ 0,
               /* GLsizei width = */ width,
               /* GLsizei height= */ height);
  }
};