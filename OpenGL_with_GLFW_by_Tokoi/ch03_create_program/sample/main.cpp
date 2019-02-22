#include <cstdlib>
#include <iostream>
#include <GLFW/glfw3.h>


int main()
{
  // GLFW の初期化 (GLFW)
  if (/* int */ glfwInit() == GL_FALSE){  // 初期化に失敗した処理
    std::cerr << "Can't initialize GLFW" << std::endl;
    return 1;
  }


  // 終了時の処理登録
  std::atexit(/* *func= */ glfwTerminate);


  // ウィンドウを作成
  GLFWwindow * const window(glfwCreateWindow(/* int          width  = */ 640,
                                             /* int          height = */ 480,
                                             /* const char  *title  = */ "Hello!",
                                             /* GLFWmonitor *monitor= */ NULL,
                                             /* GLFWwindow  *share  = */ NULL));
  if (window == NULL){  // ウィンドウ作成に失敗した処理
    std::cerr << "Can't create GLFW window." << std::endl;
    return 1;
  }

  // 作成したウィンドウを現在のウィンドウ(処理対象)とする
  glfwMakeContextCurrent(/* GLFWwindow *window= */ window);

  // 現在のウィンドウの背景色を設定
  glClearColor(/* GLfloat red   = */ 1.0f,
               /* GLfloat green = */ 1.0f,
               /* GLfloat blue  = */ 1.0f,
               /* GLfloat alpha = */ 0.0f);


  // ループ処理
  // window が開いている間繰り返す
  while (/* int */ glfwWindowShouldClose(/* GLFWwindow *window= */ window) == GL_FALSE){
    // ウィンドウを消去
    glClear(/* GLbitfield mask= */ GL_COLOR_BUFFER_BIT);  // glClear : https://www.khronos.org/registry/OpenGL-Refpages/es2.0/xhtml/glClear.xml

    // ここで描画処理

    // カラーバッファ入れ替え <= ダブルバッファリング
    glfwSwapBuffers(/* GLFWwindow *window= */ window);

    // イベント待ち (ポーリング方式)
    glfwWaitEvents();
  }

  return 0;
}

