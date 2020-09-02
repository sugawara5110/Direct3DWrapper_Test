
#include"../../../Common/Direct3DWrapper/Dx12Process.h"
#include"../../../Common/Direct3DWrapper/DxText.h"
#include"../../../Common/Window/Win.h"
#include"../../../JPGLoader/JPGLoader.h"
#include"../../../PNGLoader/PNGLoader.h"
#include"../../../Common/SearchFile/SearchFile.h"
#pragma comment(lib,"winmm.lib")
#define CURRWIDTH 1024
#define CURRHEIGHT 768
#define _CRT_SECURE_NO_WARNINGS

static Vertex ver24aa[] =
{
	{ {-1.0f, 1.0f, -1.0f}, {0.0f, 1.0f, 0.0f} ,{0.0f,0.0f}},
	{ {1.0f, 1.0f, -1.0f}, {0.0f, 1.0f, 0.0f} ,{1.0f,0.0f}},
	{ {1.0f, 1.0f, 1.0f}, {0.0f, 1.0f, 0.0f} ,{1.0f,1.0f}},
	{ {-1.0f, 1.0f, 1.0f}, {0.0f, 1.0f, 0.0f},{0.0f,1.0f} },

	{ {-1.0f, -1.0f, -1.0f}, {0.0f, -1.0f, 0.0f},{0.0f,0.0f} },
	{ {1.0f, -1.0f, -1.0f}, {0.0f, -1.0f, 0.0f} ,{1.0f,0.0f}},
	{ {1.0f, -1.0f, 1.0f}, {0.0f, -1.0f, 0.0f} ,{1.0f,1.0f}},
	{ {-1.0f, -1.0f, 1.0f}, {0.0f, -1.0f, 0.0f} ,{0.0f,1.0f}},

	{ {-1.0f, -1.0f, 1.0f}, {-1.0f, 0.0f, 0.0f} ,{0.0f,0.0f}},
	{ {-1.0f, -1.0f, -1.0f}, {-1.0f, 0.0f, 0.0f} ,{1.0f,0.0f}},
	{ {-1.0f, 1.0f, -1.0f}, {-1.0f, 0.0f, 0.0f} ,{1.0f,1.0f}},
	{ {-1.0f, 1.0f, 1.0f}, {-1.0f, 0.0f, 0.0f} ,{0.0f,1.0f}},

	{ {1.0f, -1.0f, 1.0f}, {1.0f, 0.0f, 0.0f} ,{0.0f,0.0f}},
	{ {1.0f, -1.0f, -1.0f}, {1.0f, 0.0f, 0.0f} ,{1.0f,0.0f}},
	{ {1.0f, 1.0f, -1.0f}, {1.0f, 0.0f, 0.0f} ,{1.0f,1.0f}},
	{ {1.0f, 1.0f, 1.0f}, {1.0f, 0.0f, 0.0f} ,{0.0f,1.0f}},

	{ {-1.0f, -1.0f, -1.0f}, {0.0f, 0.0f, -1.0f} ,{0.0f,0.0f}},
	{ {1.0f, -1.0f, -1.0f}, {0.0f, 0.0f, -1.0f} ,{1.0f,0.0f}},
	{ {1.0f, 1.0f, -1.0f}, {0.0f, 0.0f, -1.0f} ,{1.0f,1.0f}},
	{ {-1.0f, 1.0f, -1.0f}, {0.0f, 0.0f, -1.0f} ,{0.0f,1.0f}},

	{ {-1.0f, -1.0f, 1.0f}, {0.0f, 0.0f, 1.0f} ,{0.0f,0.0f}},
	{ {1.0f, -1.0f, 1.0f}, {0.0f, 0.0f, 1.0f} ,{1.0f,0.0f}},
	{ {1.0f, 1.0f, 1.0f}, {0.0f, 0.0f, 1.0f} ,{1.0f,1.0f}},
	{ {-1.0f, 1.0f, 1.0f}, {0.0f, 0.0f, 1.0f} ,{0.0f,1.0f}},
};

static UINT index36[] =
{
	3,1,0,
	2,1,3,

	6,4,5,
	7,4,6,

	11,9,8,
	10,9,11,

	14,12,13,
	15,12,14,

	19,17,16,
	18,17,19,

	22,20,21,
	23,20,22
};

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) {

	//ウィンドウハンドル
	HWND hWnd;
	MSG msg;
	srand((unsigned)time(NULL));

	if (Createwindow(&hWnd, hInstance, nCmdShow, CURRWIDTH, CURRHEIGHT, L"DirectX_Test") == -1)return FALSE;

	//DirectX12ラッパー
	Dx12Process::InstanceCreate();
	Dx12Process* dx = Dx12Process::GetInstance();
	Control* con = Control::GetInstance();
	DXR_Basic dxr;
	dx->dxrCreateResource();
	dx->Initialize(hWnd, CURRWIDTH, CURRHEIGHT);
	dx->setGlobalAmbientLight(0.5f, 0.5f, 0.5f);

	SearchFile* sf = new SearchFile(1);
	char** strE = new char* [2];
	strE[0] = "jpg";
	strE[1] = "png";
	sf->Search(L"./tex/*", 0, strE, 2);
	JPGLoader jpg;
	PNGLoader png;
	ARR_DELETE(strE);
	for (int i = 0; i < sf->GetFileNum(0); i++) {
		char* str = sf->GetFileName(0, i);
		UCHAR* byte = jpg.loadJPG(str, 0, 0, nullptr);
		unsigned int w = jpg.getSrcWidth();
		unsigned int h = jpg.getSrcHeight();
		if (byte == nullptr) {
			byte = png.loadPNG(str, 0, 0, nullptr);
			w = png.getSrcWidth();
			h = png.getSrcHeight();
		}

		dx->createTextureArr(sf->GetFileNum(0), i, dx->GetNameFromPass(str),
			byte, DXGI_FORMAT_R8G8B8A8_UNORM,
			w, w * 4, h);
		ARR_DELETE(byte);
	}

	//文字入力
	DxText::InstanceCreate();
	DxText* text = DxText::GetInstance();
	MeshData* md = new MeshData();
	PolygonData pd[5];
	SkinMesh* sk = new SkinMesh();
	SkinMesh* sk1 = new SkinMesh();

	md->SetCommandList(0);
	md->SetState(TRUE, TRUE, false);
	md->GetBuffer("mesh/tree.obj");
	md->SetVertex();

	sk->SetCommandList(0);
	sk->SetState(true, true);
	sk->ObjOffset(0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0);
	sk->GetFbx("mesh/player2_fbx_att.fbx");
	sk->GetBuffer(3200.0f);
	sk->SetVertex();

	sk1->SetCommandList(0);
	sk1->SetState(true, true);
	sk1->ObjOffset(0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0);
	sk1->GetFbx("mesh/player1_fbx_att.fbx");
	sk1->GetBuffer(2900.0f);
	sk1->SetVertex();

	pd[0].GetVBarray(CONTROL_POINT);
	pd[1].GetVBarray(SQUARE);
	pd[2].GetVBarray(SQUARE);
	pd[3].GetVBarray(SQUARE);
	pd[4].GetVBarray(SQUARE);
	Vertex wa[4] = {
		//左前
		-50.0f, 0.0f, 100.0f,
		0.0f, 1.0f, 0.0f,
		0.0f, 0.0f,
		//右前
		50.0f, 0.0f, 100.0f,
		0.0f, 1.0f, 0.0f,
		1.0f, 0.0f,
		//左奥
		-50.0f, 0.0f, 0.0f,
		0.0f, 1.0f, 0.0f,
		0.0f, 1.0f,
		//右奥
		50.0f, 0.0f, 0.0f,
		0.0f, 1.0f, 0.0f,
		1.0f, 1.0f
	};
	UINT ind[6] = { 0, 1, 2, 2, 1, 3 };
	pd[0].setVertex(ver24aa, sizeof(ver24aa) / sizeof(Vertex), index36, sizeof(index36) / sizeof(UINT));
	pd[1].setVertex(ver24aa, sizeof(ver24aa) / sizeof(Vertex), index36, sizeof(index36) / sizeof(UINT));
	pd[2].setVertex(ver24aa, sizeof(ver24aa) / sizeof(Vertex), index36, sizeof(index36) / sizeof(UINT));
	pd[3].setVertex(ver24aa, sizeof(ver24aa) / sizeof(Vertex), index36, sizeof(index36) / sizeof(UINT));
	pd[4].setVertex(ver24aa, sizeof(ver24aa) / sizeof(Vertex), index36, sizeof(index36) / sizeof(UINT));

	dx->Bigin(0);
	DivideArr arr[3];
	arr[0].distance = 90.0f;
	arr[0].divide = 2;//頂点数 3 → 3 * 6 = 18
	arr[1].distance = 50.0f;
	arr[1].divide = 48;//頂点数 3 → 3 * 3456 = 10368
	arr[2].distance = 36.0f;
	arr[2].divide = 96;//頂点数 3 → 3 * 13824 = 41472
	DivideArr arrsk[3];
	arr[0].distance = 90.0f;
	arr[0].divide = 2;//頂点数 3 → 3 * 6 = 18
	arr[1].distance = 50.0f;
	arr[1].divide = 6;
	arr[2].distance = 36.0f;
	arr[2].divide = 12;
	md->setDivideArr(arrsk, 3);
	sk->setDivideArr(arrsk, 3);
	md->CreateMesh();
	sk->CreateFromFBX();
	sk->setInternalAnimationIndex(0);
	sk1->CreateFromFBX();
	sk1->setInternalAnimationIndex(0);
	//dx->wireFrameTest(true);
	
	pd[0].setDivideArr(arr, 3);
	
	pd[0].Create(true, dx->GetTexNumber("wall1.jpg"),
		dx->GetTexNumber("wall1Nor.png"),
		dx->GetTexNumber("wall1.jpg"), true, true);
	pd[1].Create(true, dx->GetTexNumber("ceiling5.jpg"), /*dx->GetTexNumber("ceiling5Nor.png")*/-1, -1, true, true);
	pd[2].Create(true, dx->GetTexNumber("wave.jpg"), /*dx->GetTexNumber("waveNor.png")*/-1, -1, true, true);
	pd[3].Create(true, dx->GetTexNumber("siro.png"), -1, -1, true, true);
	pd[4].Create(true, dx->GetTexNumber("boss_magic.png"), -1, -1, true, true);
	dx->End(0);
	dx->WaitFence();
	int numMesh = sk->getNumMesh();
	int numMesh1 = sk1->getNumMesh();
	UINT numMT = 5 + numMesh + numMesh1;
	MaterialType* type = new MaterialType[numMT + 1];

	type[0] = METALLIC;
	type[1] = METALLIC;
	type[2] = METALLIC;
	type[3] = EMISSIVE;
	type[4] = METALLIC;
	for (int i = 5; i < numMesh + 5; i++)type[i] = NONREFLECTION;
	for (int i = 5 + numMesh; i < numMT; i++)type[i] = NONREFLECTION;
	type[numMT] = NONREFLECTION;
	ParameterDXR** pdx = new ParameterDXR * [numMT + 1];
	for (int i = 0; i < 5; i++)
		pdx[i] = pd[i].getParameter();
	for (int i = 5; i < numMesh + 5; i++)
		pdx[i] = sk->getParameter(i - 5);
	for (int i = 5 + numMesh; i < numMT; i++)
		pdx[i] = sk1->getParameter(i - (5 + numMesh));
	pdx[numMT] = md->getParameter();
	dxr.initDXR(0, numMT + 1, pdx, type);
	dx->SetDirectionLight(false);
	dx->DirectionLight(0.0f, 0.4f, -1.0f, 0.1f, 0.1f, 0.1f);
	float theta = 0;
	float thetaO = 0;
	float camTheta = 0;
	int insCnt = 0;
	bool rayF = false;
	T_float tfloat;

	while (1) {
		if (!DispatchMSG(&msg)) {
			break;
		}
		T_float::GetTime(hWnd);
		T_float::GetTimeUp(hWnd);

		Directionkey key = con->Direction();
		if (key == LEFT)rayF = !rayF;

		float th = tfloat.Add(0.5f);
		float th1 = tfloat.Add(0.1f);
		float ca = tfloat.Add(0.1f);

		theta = theta += th;
		if (theta > 360)theta = 0;
		thetaO = thetaO += th1;
		if (thetaO > 360)thetaO = 0;
		MATRIX thetaZ;
		VECTOR3 light1 = { 0, -40, 1 };
		VECTOR3 light2 = { 0,50,-30 };
		MatrixRotationZ(&thetaZ, theta);
		VectorMatrixMultiply(&light1, &thetaZ);
		VectorMatrixMultiply(&light2, &thetaZ);

		insCnt++;
		if (insCnt > 600) {
			insCnt = 0;
		}

		dx->PointLightPosSet(0,
			light1.x, light1.y, light1.z,
			1, 1, 1, 1, true, 1000);

		camTheta = camTheta += ca;
		if (camTheta > 360)camTheta = 0;
		MATRIX camThetaZ;
		VECTOR3 cam1 = { 0, -70, 15 };
		MatrixRotationZ(&camThetaZ, camTheta);
		VectorMatrixMultiply(&cam1, &camThetaZ);
		dx->Cameraset(cam1.x, cam1.y, cam1.z, 0, 0, 0);
		
		pd[0].InstancedMap(35, 0, 0,
			0, 0, thetaO,
			7, 7, 7);
		
		pd[0].InstanceUpdate(0, 0, 0, 0,
			1,
			4.0f);

		pd[1].InstancedMap(-35, 0, 0,
			0, 0, thetaO,
			7, 7, 7);
		
		pd[1].InstanceUpdate(0, 0, 0, 0,
			0,
			4.0f);

		pd[2].InstancedMap(0, 0, -25,
			0, 0, 0,
			60, 60, 15);
		pd[2].InstanceUpdate(0, 0, 0, 0,
			0,
			4.0f);

		pd[3].InstancedMap(light1.x, light1.y, light1.z,
			0, 0, 0,
			1, 1, 1);
		pd[3].InstanceUpdate(0, 0, 0, 0,
			0,
			4.0f);

		pd[4].InstancedMap(0, 0, 15,
			0, 0, thetaO,
			4, 4, 4);
		pd[4].InstanceUpdate(0, 0, 0, 0,
			0,
			4.0f);


		float m = tfloat.Add(2.0f);

		sk->Update(0,m,
			15, 0, 0,
			0, 0, 0, 0,
			0, 0, 0,
			1.2f);
		sk1->Update(m,
			-15, 0, 0,
			0, 0, 0, 0,
			0, 0, 0,
			1.2f);

		md->Update(0, 0, -10,
			0, 0, 0, 0,
			0, 0, 0,
			1, 1);

		if (!rayF) {
			dx->Bigin(0);
			dx->BiginDraw(0);
			sk->Draw();
			sk1->Draw();
			pd[0].Draw();
			pd[1].Draw();
			pd[2].Draw();
			pd[3].Draw();
			pd[4].Draw();
			md->Draw();
			dx->EndDraw(0);
			dx->End(0);
			dx->WaitFence();
		}
		else {
			sk->StreamOutput();
			sk1->StreamOutput();
			pd[0].StreamOutput();
			pd[1].StreamOutput();
			pd[2].StreamOutput();
			pd[3].StreamOutput();
			pd[4].StreamOutput();
			md->StreamOutput();

			dx->Bigin(0);
			dxr.raytrace(0);
			dx->End(0);
			dx->WaitFence();
		}
		dx->DrawScreen();
	}

	ARR_DELETE(type);
	ARR_DELETE(pdx);
	S_DELETE(sk);
	S_DELETE(sk1);
	S_DELETE(sf);
	S_DELETE(md);
	Control::DeleteInstance();
	DxText::DeleteInstance();
	Dx12Process::DeleteInstance();
	return 0;
}