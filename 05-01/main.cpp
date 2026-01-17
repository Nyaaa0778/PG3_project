#include <Novice.h>

const char kWindowTitle[] = "LE2B_28_ヤマダ_ナオ";

struct Vector3 {
  float x;
  float y;
  float z;
};

class Player {
public:
  Player() {}

  void Initialize() { pos_ = {640.0f, 360.0f, 0.0f}; }
  void Update() {}
  void Draw() {
    Novice::DrawEllipse((int)pos_.x, (int)pos_.y, 20, 20, 0.0f, WHITE,
                        kFillModeSolid);
  }

  void MoveRight() { pos_.x += speed_; }
  void MoveLeft() { pos_.x -= speed_; }

private:
  Vector3 pos_;
  float speed_ = 4.0f;
};

class ICommand {
public:
  virtual ~ICommand() {}
  virtual void Exec(Player &player) = 0;
};

class MoveRightCommand : public ICommand {
public:
  void Exec(Player &player) override { player.MoveRight(); }
};

class MoveLeftCommand : public ICommand {
public:
  void Exec(Player &player) override { player.MoveLeft(); }
};

enum SCENE { TITLE, STAGE, CLEAR };

class IScene {
protected:
  // シーン番号管理用の変数
  static int sceneNo;

public:
  // 純粋仮想関数
  virtual void Initialize() = 0;
  virtual void Update() = 0;
  virtual void Draw() = 0;

  // 仮想デストラクタ
  virtual ~IScene() {}

  // シーンのゲッター
  int GetSceneNo() { return sceneNo; }
};

int IScene::sceneNo = STAGE;

class InputHandler {
public:
  ~InputHandler() {
    delete pressKeyA_;
    delete pressKeyD_;
  }

  ICommand *HandleInput() {
    if (Novice::CheckHitKey(DIK_D)) {
      return pressKeyD_;
    }

    if (Novice::CheckHitKey(DIK_A)) {
      return pressKeyA_;
    }

    return nullptr;
  }

  void AssignMoveLeftCommand2PressKeyA() {
    ICommand *command = new MoveLeftCommand();
    pressKeyA_ = command;
  }
  void AssignMoveRightCommand2PressKeyD() {
    ICommand *command = new MoveRightCommand();
    pressKeyD_ = command;
  }

private:
  ICommand *pressKeyA_ = nullptr;
  ICommand *pressKeyD_ = nullptr;
};

class StageScene : public IScene {
private:
  InputHandler *inputHandler_ = nullptr;
  ICommand *iCommand_ = nullptr;
  Player *player_ = nullptr;

public:
  StageScene() {}

  ~StageScene() override {
    delete player_;
    delete inputHandler_;
  }

  void Initialize() override {
    inputHandler_ = new InputHandler();

    // Assign command
    inputHandler_->AssignMoveRightCommand2PressKeyD();
    inputHandler_->AssignMoveLeftCommand2PressKeyA();

    // new Player
    player_ = new Player();
    player_->Initialize();
  }
  void Update() override {
    // get Input
    iCommand_ = inputHandler_->HandleInput();

    // set command
    if (iCommand_) {
      iCommand_->Exec(*player_);
    }

    player_->Update();
  }
  void Draw() override { player_->Draw(); }
};

// Windowsアプリでのエントリーポイント(main関数)
int WINAPI WinMain(_In_ HINSTANCE, _In_opt_ HINSTANCE, _In_ LPSTR, _In_ int) {

  // ライブラリの初期化
  Novice::Initialize(kWindowTitle, 1280, 720);

  // キー入力結果を受け取る箱
  char keys[256] = {0};
  char preKeys[256] = {0};

  StageScene stageScene;
  stageScene.Initialize();

  // ウィンドウの×ボタンが押されるまでループ
  while (Novice::ProcessMessage() == 0) {
    // フレームの開始
    Novice::BeginFrame();

    // キー入力を受け取る
    memcpy(preKeys, keys, 256);
    Novice::GetHitKeyStateAll(keys);

    ///
    /// ↓更新処理ここから
    ///

    // 更新処理
    stageScene.Update();

    ///
    /// ↑更新処理ここまで
    ///

    ///
    /// ↓描画処理ここから
    ///

    // 描画処理
    stageScene.Draw();

    ///
    /// ↑描画処理ここまで
    ///

    // フレームの終了
    Novice::EndFrame();

    // ESCキーが押されたらループを抜ける
    if (preKeys[DIK_ESCAPE] == 0 && keys[DIK_ESCAPE] != 0) {
      break;
    }
  }

  // ライブラリの終了
  Novice::Finalize();
  return 0;
}
