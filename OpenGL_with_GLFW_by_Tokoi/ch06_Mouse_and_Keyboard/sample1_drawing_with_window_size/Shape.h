#pragma once
#include <memory>
// 図形データ
#include "Object.h"

class Shape
// 図形データ
{
  // > ○○くんのために一所懸命書いたものの結局○○くんの卒業に間に合わなかったGLFW による OpenGL 入門 - p80
  // > object を shared_ptr にしておけば,同じ Object クラスのインスタンスを参照している Shape クラスのインスタンスが
  // > すべて削除されたときに,そのインスタンス自体が削除されます
  // > こうすることにより,コピーコンストラクタや代入によるインスタンスのコピーが可能になります.
  // > これを使うために標準テンプレートライブラリの memory を #include します。
  std::shared_ptr<const Object> object;

protected:
  // 描画に使う頂点の数
  // > ○○くんのために一所懸命書いたものの結局○○くんの卒業に間に合わなかったGLFW による OpenGL 入門 - p80
  // > このメンバは派生クラスからも参照するので、protected にしておきます
  const GLsizei vertex_count;

public:
  /**
   * @param | dim_size      | const GLint          | 頂点の位置の次元
   * @param | vertex_count  | const GLsizei        | 頂点の数
   * @param | *vertex_array | const Object::Vertex | 頂点属性を格納した配列
   */
  Shape(const GLint          dim_size,
        const GLsizei        vertex_count,
        const Object::Vertex *vertex_array)
      : object(new Object(/* const GLint   dim_size     = */ dim_size,
                          /* const GLsizei vertex_count = */ vertex_count,
                          /* const Vertex  *vertex_array= */ vertex_array)),
        vertex_count(/* GLsizei */ vertex_count)
  {
  }
  // 描画
  void draw() const
  {
    // 頂点配列オブジェクトを結合する
    object->bind();
    // 描画を実行する
    execute();
  }
  // 描画の実行
  virtual void execute() const
  {
    // 折れ線で描画する
    glDrawArrays(GL_LINE_LOOP, 0, vertex_count);
  }
};