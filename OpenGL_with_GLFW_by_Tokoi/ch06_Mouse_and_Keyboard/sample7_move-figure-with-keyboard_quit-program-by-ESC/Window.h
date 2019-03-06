// @author pollenjp

#pragma once
#include <iostream>
#include <GL/glew.h>
#include <GLFW/glfw3.h>

// ウィンドウ関連の処理
class Window
{
private:
  // ウィンドウのハンドル
  GLFWwindow * const window;
  // ウィンドウのサイズ
  GLfloat size[2];  // (width, height)
  // ワールド座標系に対するデバイス座標系の拡大率
  GLfloat scale;
  // 図形の正規化デバイス座標系上での位置
  GLfloat location[2];
  // キーボードの状態
  int keyStatus;

public:
  // @brief constructor
  // @param (int          width ) window width
  // @param (int          height) window height
  // @param (const char * title ) title string
  Window(int        width  = 640,
         int        height = 480,
         const char *title = "Hello!"):
         // create window
         window(/* LFWwindow * */glfwCreateWindow(/* int           width  = */width,
                                                  /* int           height = */height,
                                                  /* const char  * title  = */title,
                                                  /* GLFWmonitor * monitor= */NULL,
                                                  /* GLFWwindow  * share  = */NULL)),
         scale(/* GLfloat */100.0f),
         location{0.0f, 0.0f},
         keyStatus(GLFW_RELEASE)
  {
    if (this->window == NULL){  // if you fail in creating a window (ウィンドウ作成に失敗した処理)
      std::cerr << "Can't create GLFW window." << std::endl;
      exit(1);  // interupt
    }
    std::cout << "Created GLFW window!" << std::endl;

    // 作成したウィンドウを現在のウィンドウ(処理対象)とする
    glfwMakeContextCurrent(/* GLFWwindow *window= */this->window);
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

    // @brief マウスホイール操作時に呼び出す処理の登録
    // > wheel(GLFWwindow *const window, double x, double y)
    glfwSetScrollCallback(/* GLFWwindow * window= */this->window, /* GLFWscrollfun cbfun= */wheel);

    // キーボード操作時に呼び出す処理の登録
    glfwSetKeyCallback(/* GLFWwindow * const window= */this->window, /* GLFWkeyfun cbfun= */this->keyboard);

    // @brief このインスタンスの this ポインタを記録しておく
    // @detail
    //   > ○○くんのために一所懸命書いたものの結局○○くんの卒業に間に合わなかったGLFW による OpenGL 入門 - p92
    //     静的メンバ関数はインスタンスを生成していない (すなわち,メンバ変数にメモリが割り当てられていない) ときにも
    //     呼び出せるかわりに,その中でメンバ変数を参照することができません. 静的メンバ関数内でメンバ変数を参照する
    //     ためには,そのインスタンスの実体 (割り当てられたメモリ) の場所を知る必要があります.
    //   > [glfwSetWindowUserPointer() - GLFW: Window reference](https://www.glfw.org/docs/latest/group__window.html#ga3d2fc6026e690ab31a13f78bc9fd3651)
    glfwSetWindowUserPointer(/* GLFWwindow * window = */this->window, /* void * pointer= */this);

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
    glfwSetWindowSizeCallback(/* GLFWwindow *const window= */this->window, /* GLFWwindowsizefun cbfun= */this->resize);

    // 開いたウィンドウの初期設定
    // this also initialize ths->size
    resize(/* GLFWwindow * const window= */this->window, /* int width= */width, /* int height*/height);
  }

  // @brief destructor
  virtual ~Window()
  {
    // 指定されたウィンドウとそのコンテキストを破棄
    // > [GLFW: Window reference](https://www.glfw.org/docs/latest/group__window.html#gacdf43e51376051d2c091662e9fe3d7b2)
    glfwDestroyWindow(/* GLFWwindow *window= */this->window);
  }

  // @brief accessor 位置を取り出す
  const GLfloat *getLocation() const { return this->location; }

  // @brief accessor ワールド座標系に対するデバイス座標系の拡大率を取り出す
  GLfloat getScale() const { return this->scale; }

  // @brief accessor ウィンドウのサイズを取り出す
  const GLfloat * getSize() const { return this->size; }

  //  @brief static method キーボード操作時の処理 (callback function of glfwSetKeyCallback)
  //  @param (GLFWwindow *const window) キーボード操作の対象となったウィンドウのハンドル
  //  @param (int key) 操作されたキー. これは glfwGetKey() の引数 key に指定するものと同じ.
  //  @param (int scancode) 操作されたキーのスキャンコード. この値はプラットフォームに依存している.
  //  @param (int action)
  //    GLFW_RELEASE (0) : 離したとき
  //    GLFW_PRESS   (1) : キーを押したとき
  //    GLFW_REPEAT  (2) : キーリピート機能が働いたとき
  //  @param (int mods) key と同時に押した Shift などのモディファイア (修飾) キー. 以下のキーが同時に押されたとき.
  //    Shift : GLFW_MOD_SHIFT (0x0001),
  //    Ctrl  : GLFW_MOD_CONTROL (0x0002),
  //    ALT   : GLFW_MOD_ALT (0x0004),
  //    Windows,Command,Superキー : GLFW_MOD_SUPER (0x0008) キー,
  //    複数のモディファイアキーを同時に押しているときは,これらのビット論理和が格納
  //  @detail
  //    > ○○くんのために一所懸命書いたものの結局○○くんの卒業に間に合わなかったGLFW による OpenGL 入門 - p112
  static void keyboard(GLFWwindow * const window,
                       int                key,
                       int                scancode,
                       int                action,
                       int                mods)
  {
    // このインスタンスの this ポインタを得る
    Window * const instance(
      static_cast<Window *>(/* void * */glfwGetWindowUserPointer(/* GLFWwindow * window= */window)));
    if (instance != NULL)
    {
      std::cout << "Get instance pointer!" << std::endl;
      // キーの状態を保存する
      instance->keyStatus = action;
    } else {  // if instace is null
      std::cerr << "`instance` variable in Window.keyboard() is NULL (null pointer)." << std::endl;
    }
}

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
  static void resize(GLFWwindow * const window,
                      int               width,
                      int               height)
  {
    // ウィンドウ全体をビューポートに設定する
    // [glViewport](https://www.khronos.org/registry/OpenGL-Refpages/es2.0/xhtml/glViewport.xml)
    glViewport(/* GLint   x     = */ 0,
               /* GLint   y     = */ 0,
               /* GLsizei width = */ width,
               /* GLsizei height= */ height);

    // このインスタンスの this ポインタを得る
    // 静的関数内ではprivateメンバにアクセスできないためインスタンス(this)を指すポインタを取得しそれを経由する
    Window * const instance(
      static_cast<Window *>(/* void * */glfwGetWindowUserPointer(/* GLFWwindow * window= */window)));

    if (instance != NULL)
    {
      std::cout << "Get instance pointer!" << std::endl;
      // 開いたウィンドウのサイズを保存する
      instance->size[0] = static_cast<GLfloat>(width);
      instance->size[1] = static_cast<GLfloat>(height);
    } else {  // if instace is null pointer
      std::cerr << "`instance` variable in Window.resize() is NULL (null pointer)." << std::endl;
    }

  }

  // @brief method ウィンドウを閉じるべきかを判定する
  int shouldClose() const
  {
    return glfwWindowShouldClose(/* GLFWwindow *window= */this->window)
           || glfwGetKey(/* GLFWwindow * window= */this->window, /* int key = */GLFW_KEY_ESCAPE) == GLFW_PRESS;
  }

  // @brief method カラーバッファを入れ替えてイベントを取り出す.
  // @detail イベント待ちのあとにイベント処理を書いている
  void swapBuffers()
  {
    // カラーバッファ入れ替え <= ダブルバッファリング
    glfwSwapBuffers(/* GLFWwindow *window= */this->window);

    // イベントを取り出す
    // > ○○くんのために一所懸命書いたものの結局○○くんの卒業に間に合わなかったGLFW による OpenGL 入門 - p42
    //   ポーリング方式
    // > ○○くんのために一所懸命書いたものの結局○○くんの卒業に間に合わなかったGLFW による OpenGL 入門 - p110
    //   そこでイベントの取り出しを,キーを押している間は glfwPollEvents() で行い,キーを押していないときは
    //   glfwWaitEvents() で行うようにします. glfwSetKeyCallback() 関数を用いれば,任意のキーを操作したときに
    //   実行するコールバック関数を指定できるので,その中でこの切り替えを行います
    if(this->keyStatus == GLFW_RELEASE){
      // keyが押されていない場合
      // > ○○くんのために一所懸命書いたものの結局○○くんの卒業に間に合わなかったGLFW による OpenGL 入門 - p109
      //   glfwWaitEvents() はイベントが発生したときにプログラムの実行を再開しますが,キーを押し続けている状態では
      //   キーリピート機能が働くまでイベントは発生しませんから,それまでプログラムが停止したまま
      glfwWaitEvents();
    } else {
      // GLFW_PRESS, GLFW_REPEAT(キーリピート) のとき
      // > ○○くんのために一所懸命書いたものの結局○○くんの卒業に間に合わなかったGLFW による OpenGL 入門 - p39
      //   時間とともに画面の表示を更新するアニメーションなどの場合はイベントの発生を待たないglfwPollEvents()関数
      glfwPollEvents();
    }

    // キーボードの状態を調べる
    // x move
    if (glfwGetKey(/* GLFWwindow * window= */this->window, /* int key   = */GLFW_KEY_LEFT) == GLFW_PRESS)
                                                      { this->location[0] -= 2.0f / this->size[0]; }
    else if (glfwGetKey(this->window, GLFW_KEY_RIGHT) == GLFW_PRESS){ this->location[0] += 2.0f / this->size[0]; }
    // y move
    if      (glfwGetKey(this->window, GLFW_KEY_DOWN) == GLFW_PRESS){ this->location[1] -= 2.0f / this->size[1]; }
    else if (glfwGetKey(this->window, GLFW_KEY_UP)   == GLFW_PRESS){ this->location[1] += 2.0f / this->size[1]; }

    // マウスの左ボタンの状態を調べる
    // > [glfwGetMouseButton() - GLFW: Input reference](https://www.glfw.org/docs/latest/group__input.html#gac1473feacb5996c01a7a5a33b5066704)
    //   Returns One of GLFW_PRESS(1) or GLFW_RELEASE(0)
    // > ○○くんのために一所懸命書いたものの結局○○くんの卒業に間に合わなかったGLFW による OpenGL 入門 - p105
    //   GLFW_MOUSE_BUTTON_1 と GLFW_MOUSE_BUTTON_LEFT は左ボタン
    //   GLFW_MOUSE_BUTTON_2 と GLFW_MOUSE_BUTTON_RIGHT は右ボタン
    //   GLFW_MOUSE_BUTTON_3 と GLFW_MOUSE_BUTTON_MIDDLE は中ボタン
    // glfwGetMouseButton
    if (glfwGetMouseButton(/* GLFWwindow * window= */this->window,
                           /* int          button= */GLFW_MOUSE_BUTTON_1) != GLFW_RELEASE){
      // マウスの左ボタンが押されていたらマウスカーソルの位置を取得する
      double x, y;
      // > [glfwGetCursorPos() - GLFW: Input reference](https://www.glfw.org/docs/latest/group__input.html#ga01d37b6c40133676b9cea60ca1d7c0cc)
      glfwGetCursorPos(/* GLFWwindow * window= */this->window,
                       /* double     * xpos  = */&x,
                       /* double     * ypos  = */&y);
      // マウスカーソルの正規化デバイス座標系上での位置を求める
      // > ○○くんのために一所懸命書いたものの結局○○くんの卒業に間に合わなかったGLFW による OpenGL 入門 - p102
      //   マウスカーソルの座標系の原点はウィンドウの左上
      this->location[0] = static_cast<GLfloat>(x) * 2.0f / this->size[0] - 1.0f;
      this->location[1] = 1.0f - static_cast<GLfloat>(y) * 2.0f / this->size[1];
    }
  }

  // マウスホイール操作時の処理
  static void wheel(GLFWwindow *window, double x, double y)
  {
    // このインスタンスの this ポインタを得る
    Window *const instance(static_cast<Window *>(/* void * */glfwGetWindowUserPointer(/* GLFWwindow * 	window= */window)));
    if (instance != NULL)
    {
      std::cout << "Get instance pointer!" << std::endl;
      // ワールド座標系に対するデバイス座標系の拡大率を更新する
      instance->scale += static_cast<GLfloat>(y);
    } else {  // if instace is null pointer
      std::cerr << "`instance` variable in Window.wheel() is NULL (null pointer)." << std::endl;
    }
  }
};
