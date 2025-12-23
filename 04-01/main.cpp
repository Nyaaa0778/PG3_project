#include <Novice.h>

#include <cmath>
#include <memory>

const char kWindowTitle[] = "04-01";

struct Vector2 {
  float x;
  float y;
};

class Player {
public:
  void Initialize() {
    pos_ = {200.0f, 300.0f};
    radius_ = 30.0f;
    speed_ = 5.0f;
  }

  void Update(const char *keys) {
    if (keys[DIK_W]) {
      pos_.y -= speed_;
    }

    if (keys[DIK_S]) {
      pos_.y += speed_;
    }

    if (keys[DIK_A]) {
      pos_.x -= speed_;
    }
    if (keys[DIK_D]) {
      pos_.x += speed_;
    }
  }

  void Draw() {
    Novice::DrawEllipse(static_cast<int>(pos_.x), static_cast<int>(pos_.y),
                        static_cast<int>(radius_), static_cast<int>(radius_),
                        0.0f, 0x0000FFFF, kFillModeSolid);
  }

  const Vector2 &GetPos() const { return pos_; }
  float GetRadius() const { return radius_; }

private:
  Vector2 pos_{};
  float radius_ = 0.0f;
  float speed_ = 0.0f;
};

class Enemy {
public:
  void Initialize() {
    pos_ = {400.0f, 300.0f};
    radius_ = 50.0f;
    isHit_ = false;
  }

  void Draw() {
    if (isHit_) {
      return;
    }

    Novice::DrawEllipse(static_cast<int>(pos_.x), static_cast<int>(pos_.y),
                        static_cast<int>(radius_), static_cast<int>(radius_),
                        0.0f, 0xFF0000FF, kFillModeSolid);
  }

  const Vector2 &GetPos() const { return pos_; }
  float GetRadius() const { return radius_; }
  void IsHit(bool isHit) { isHit_ = isHit; }

private:
  Vector2 pos_{};
  float radius_ = 0.0f;
  bool isHit_ = false;
};

class Bullet {
public:
  void Initialize() {
    pos_ = {0.0f, 0.0f};
    radius_ = 8.0f;
    speed_ = 10.0f;
    isActive_ = false;
  }

  void Update(const char *keys, const char *preKeys, const Vector2 &playerPos) {

    // 発射（SPACE押した瞬間）
    if (!isActive_ && preKeys[DIK_SPACE] == 0 && keys[DIK_SPACE] != 0) {
      isActive_ = true;
      pos_ = playerPos; // プレイヤー位置から出す
    }

    if (!isActive_) {
      return;
    }

    // 移動
    pos_.x += speed_;

    // 画面外で消す
    if (pos_.x > 1280.0f + radius_) {
      isActive_ = false;
    }
  }

  void Draw() {
    if (!isActive_) {
      return;
    }

    Novice::DrawEllipse((int)pos_.x, (int)pos_.y, (int)radius_, (int)radius_,
                        0.0f, 0xFFFFFFFF, kFillModeSolid);
  }

  void IsActive(bool isActive) { isActive_ = isActive; }
  const Vector2 &GetPos() const { return pos_; }
  float GetRadius() const { return radius_; }

private:
  Vector2 pos_{};
  float radius_ = 0.0f;
  float speed_ = 0.0f;
  bool isActive_ = false;
};

enum SCENE { TITLE, STAGE, CLEAR };

class IScene {
protected:
  // シーン番号管理用の変数
  static int sceneNo;

public:
  // 純粋仮想関数
  virtual void Initialize() = 0;
  virtual void Update(const char *keys, const char *preKeys) = 0;
  virtual void Draw() = 0;

  // 仮想デストラクタ
  virtual ~IScene() {}

  // シーンのゲッター
  int GetSceneNo() { return sceneNo; }
};

int IScene::sceneNo = TITLE;

class TitleScene : public IScene {
public:
  void Initialize() override {}
  void Update(const char *keys, const char *preKeys) override {
    if (keys[DIK_SPACE] && !preKeys[DIK_SPACE]) {
      sceneNo = STAGE;
    }
  }
  void Draw() override { Novice::ScreenPrintf(20, 20, "TITLE"); }
};

class StageScene : public IScene {
public:
  ~StageScene() {
    delete bullet_;
    delete enemy_;
    delete player_;
  }

  void Initialize() override {
    player_ = new Player();
    player_->Initialize();

    enemy_ = new Enemy();
    enemy_->Initialize();

    bullet_ = new Bullet();
    bullet_->Initialize();
  }
  void Update(const char *keys, const char *preKeys) override {
    player_->Update(keys);

    bullet_->Update(keys, preKeys, player_->GetPos());

    // 当たり判定
    if (bullet_->GetRadius() + enemy_->GetRadius() >=
        sqrtf(powf(bullet_->GetPos().x - enemy_->GetPos().x, 2) +
              powf(bullet_->GetPos().y - enemy_->GetPos().y, 2))) {
      enemy_->IsHit(true);
      bullet_->IsActive(false);

      sceneNo = CLEAR;
    }
  }
  void Draw() override {
    bullet_->Draw();

    player_->Draw();

    enemy_->Draw();

    Novice::ScreenPrintf(20, 20, "STAGE");
  }

private:
  Player *player_ = nullptr;
  Enemy *enemy_ = nullptr;
  Bullet *bullet_ = nullptr;
};

class ClearScene : public IScene {
public:
  void Initialize() override {}
  void Update(const char *keys, const char *preKeys) override {
    if (keys[DIK_SPACE] && !preKeys[DIK_SPACE]) {
      sceneNo = TITLE;
    }
  }
  void Draw() override { Novice::ScreenPrintf(20, 20, "CLEAR"); }
};

class GameManager {
  // シーン保持用のメンバ変数
  std::unique_ptr<IScene> sceneArr_[3];

  // どのシーンを呼び出すかを管理する変数
  int currentSceneNo_; // 現在のシーン
  int prevSceneNo_;    // 前のシーン
  int sceneNo_ = TITLE;

public:
  GameManager() {
    // 各シーン配列
    sceneArr_[TITLE] = std::make_unique<TitleScene>();
    sceneArr_[STAGE] = std::make_unique<StageScene>();
    sceneArr_[CLEAR] = std::make_unique<ClearScene>();

    // 初期シーンの設定
    currentSceneNo_ = TITLE;
    prevSceneNo_ = TITLE;
    sceneArr_[currentSceneNo_]->Initialize();
  }

  ~GameManager() {}

  int Run() {
    // キー入力結果を受け取る箱
    char keys[256] = {0};
    char preKeys[256] = {0};

    while (Novice::ProcessMessage() == 0) {
      Novice::BeginFrame(); // フレームの開始

      memcpy(preKeys, keys, 256);
      Novice::GetHitKeyStateAll(keys);

      // シーンのチェック
      prevSceneNo_ = currentSceneNo_;
      currentSceneNo_ = sceneArr_[currentSceneNo_]->GetSceneNo();

      // シーン変更チェック
      if (prevSceneNo_ != currentSceneNo_) {
        sceneArr_[currentSceneNo_]->Initialize();
      }

      sceneArr_[currentSceneNo_]->Update(keys, preKeys);
      sceneArr_[currentSceneNo_]->Draw();

      Novice::EndFrame();

      if (preKeys[DIK_ESCAPE] == 0 && keys[DIK_ESCAPE] != 0) {
        break;
      }
    }

    return 0;
  }
};

// Windowsアプリでのエントリーポイント(main関数)
int WINAPI WinMain(_In_ HINSTANCE, _In_opt_ HINSTANCE, _In_ LPSTR, _In_ int) {

  // ライブラリの初期化
  Novice::Initialize(kWindowTitle, 1280, 720);

  GameManager *gameManager = new GameManager();
  gameManager->Run();

  delete gameManager;

  // ライブラリの終了
  Novice::Finalize();
  return 0;
}
