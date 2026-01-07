#include "PlayScene.h"
#include "Player.h"
#include "Field.h"
#include "Common.h"
#include "../Library/SceneManager.h"
#include "../Library/ObjectManager.h"

PlayScene::PlayScene()
{
    m_readyGo = new ReadyGoManager();
    int stage = SceneManager::GetNextStage();
    new Field(stage);

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

    
    
}

void PlayScene::Draw()
{
    DrawString(0, 0, "PLAY SCENE", GetColor(255, 255, 255));
   
    ObjectManager::Draw();
    m_readyGo->Draw();
}