# ch06 Mouse and Keyboard - sample7_move-figure-with-keyboard_quit-program-by-ESC/

- 6.3 キーボードで図形を動かす
    - 6.3.1 ESC キーでプログラムを終了する
    - 6.3.2 矢印キーで図形を移動する
        - Window クラス (Window.h) の変更点
        - スムーズに動かす
        - 消費電力をケチる

---

- [Execute](#Execute)

---


## Execute

```
$ make
```

__Window クラス (Window.h) の変更点__
`glfwWaitEvents()` (キーリピート機能が働くまでイベントは発生しませんから、それまでプログラムが停止したまま)
![](./img/execute1.gif)

__スムーズに動かす__
`glfwPollEvents()` (こっちのほうがキーを押しっぱなしの時のスタートの滑らかさが高い)
![](./img/execute2.gif)

__消費電力をケチる__
常に`glfwPollEvents()`を使っているときはずっと描画し続けていた(while loop の index カウントされ続けていた). しかし以下のGIFではそれが改善され,入力したときだけ while loop の index が増加しているのがわかる.
![](./img/execute3.gif)

---

