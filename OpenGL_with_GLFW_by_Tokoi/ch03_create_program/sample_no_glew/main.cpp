#include <cstdlib>
#include <iostream>
#include <GLFW/glfw3.h>


int main()
{
  ////////////////////////////////////////////////////////////////////////////////
  // GLFW の初期化 (GLFW)
  if (glfwInit() == GL_FALSE){
    // 初期化に失敗した処理
    std::cerr << "Can't initialize GLFW" << std::endl;
    return 1;
  }


  ////////////////////////////////////////////////////////////////////////////////
  // 終了時の処理登録 (GLFW)
  atexit(glfwTerminate);


  ////////////////////////////////////////////////////////////////////////////////
  // ウィンドウを作成 (GLFW)
  GLFWwindow * const window(glfwCreateWindow(/* int           width   = */ 640,
                                             /* int           height  = */ 480,
                                             /* const char  * title   = */ "Hello!",
                                             /* GLFWmonitor * monitor = */ NULL,
                                             /* GLFWwindow  * share   = */ NULL));
  if (window == NULL){
    // ウィンドウ作成に失敗した処理
    std::cerr << "Can't create GLFW window." << std::endl;
    return 1;
  }

  // 作成したウィンドウを処理対象とする (GLFW)
  glfwMakeContextCurrent(/* GLFWwindow *  window = */ window);

  // 背景色 (OpenGL)
  glClearColor(/* GLfloat red   = */ 1.0f,
               /* GLfloat green = */ 1.0f,
               /* GLfloat blue  = */ 1.0f,
               /* GLfloat alpha = */ 0.0f);


  ////////////////////////////////////////////////////////////////////////////////
  // ループ処理

  // ウィンドウが開いている間繰り返す
  while (glfwWindowShouldClose(/* GLFWwindow * window = */ window) == GL_FALSE){
    // ウィンドウを消去 (GLFW)
    glClear(/* GLbitfield mask = */ GL_COLOR_BUFFER_BIT);

    // 描画処理

    // カラーバッファ入れ替え <= ダブルバッファリング (GLFW)
    glfwSwapBuffers(window);

    // イベント待ち (GLFW)
    glfwWaitEvents();
  }

  return 0;
}

