///////////////////////////////////////////////SkinObj/////////////////////////////////////////////////////

#include "SkinObj.h"

void SkinObj::create() {
	sk = std::make_unique<SkinMesh>();
	sk->SetState(true, true);
	//sk->GetFbx("mesh/p1/player1_all.fbx");//このモデルスペキュラが明るすぎ
	sk->GetFbx("../../../texturePPM/player1_fbx_att.fbx");
	float end[2] = { 4000,1000 };
	sk->GetBuffer(1, 1, end);

	//sk->GetFbxSub("mesh/p1/player1_Run.fbx", 1);
	//sk->GetBuffer_Sub(1, 400);

	//sk->GetFbxSub("mesh/p1/player1_Hook.fbx", 2);
	//sk->GetBuffer_Sub(2, 1000);

	//sk->GetFbxSub("mesh/p1/player1_kick.fbx", 3);
	//float end1[3] = { 3000,3000,3000 };
	//sk->GetBuffer_Sub(3, 3, end1);

	sk->SetVertex(true, true);
	sk->SetConnectStep(0, 10000);
	//sk->SetConnectStep(1, 1000);
	//sk->SetConnectStep(2, 10000);
	//sk->SetConnectStep(3, 10000);
	sk->CreateFromFBX(0);
	//sk->CreateFromFBX_SubAnimation(1);
	//sk->CreateFromFBX_SubAnimation(2);
	//sk->CreateFromFBX_SubAnimation(3);
}

static T_float tfloat;

void SkinObj::update() {
	switch (DxInput::GetInstance()->checkKeyActionNo()) {
	case DIK_NUMPAD0:
		break;
	case DIK_NUMPAD1:
		break;
	case DIK_NUMPAD2:
		break;
	case DIK_NUMPAD3:
		break;
	case DIK_NUMPAD4:
		break;
	case DIK_NUMPAD5:
		break;
	case DIK_NUMPAD6:
		break;
	case DIK_NUMPAD7:
		break;
	case DIK_NUMPAD8:
		break;
	case DIK_NUMPAD9:
		break;
	case DIK_A:
		meshIndex = 0;
		internalIndex = 0;
		break;
	case DIK_S:
		meshIndex = 0;
		internalIndex = 1;
		break;
	case DIK_D:
		meshIndex = 1;
		internalIndex = 0;
		break;
	case DIK_F:
		meshIndex = 2;
		internalIndex = 0;
		break;
	case DIK_G:
		meshIndex = 3;
		internalIndex = 0;
		break;
	case DIK_H:
		meshIndex = 3;
		internalIndex = 1;
		break;
	case DIK_J:
		meshIndex = 3;
		internalIndex = 2;
		break;
	}
	float m = tfloat.Add(1.0f);
	/*if (sk->Update(meshIndex, m, {0,0,-15}, {0,0,0,0}, {-90,0,theta}, {0.02f,0.02f,0.02f}, internalIndex) && meshIndex != 1) {
		meshIndex = 0;
	}*/
	//sk->Update(meshIndex, m, { -20,0,-15 }, { 0,0,0,0 }, { -90,0,theta }, { 0.02f,0.02f,0.02f }, internalIndex);
	sk->Update(meshIndex, m, { -20,0,15 }, { 0,0,0,0 }, { -90,0,theta }, { 2.0f,2.0f,2.0f }, internalIndex);
}

void SkinObj::Draw(int comNo) {
	sk->Draw(comNo);
}

void SkinObj::StreamOutput(int comNo) {
	sk->StreamOutput(comNo);
}

ParameterDXR* SkinObj::getParameterDXR(int index) {
	return sk->getParameter(index);
}

int SkinObj::getNumParameterDXR() {
	return sk->getNumMesh();
}