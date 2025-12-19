#include "PlayScene.h"
#include "Player.h"
#include "Field.h"
#include "Common.h"
#include "../Library/SceneManager.h"
#include "../Library/ObjectManager.h"

PlayScene::PlayScene()
{
    m_readyGo = new ReadyGoManager();
    new Field(1);

}

PlayScene::~PlayScene()
{
    if (m_readyGo) {
        delete m_readyGo;
        m_readyGo = nullptr;
    }
}

void PlayScene::Update()
{

    m_readyGo->Update();


    if (m_readyGo->IsActive()) {
 
        return;
    }

    ObjectManager::Update();

    
    if (CheckHitKey(KEY_INPUT_T)) {
        SceneManager::ChangeScene("TITLE");
    }
}

void PlayScene::Draw()
{
    DrawString(0, 0, "PLAY SCENE", GetColor(255, 255, 255));
    DrawString(100, 400, "Push [T]Key To Title", GetColor(255, 255, 255));

    ObjectManager::Draw();
    m_readyGo->Draw();
}