
//////////////////////////////////////DirectXテスト/////////////////////////////////////////////////////////////

#include"../../../Common/Direct3DWrapper/Dx12Process.h"
#include"../../../Common/Direct3DWrapper/DxText.h"
#include"../../../Common/Window/Win.h"
#include"../../../JPGLoader/JPGLoader.h"
#include"../../../PNGLoader/PNGLoader.h"
#include"../../../Common/SearchFile/SearchFile.h"
#include"../../../Common/DirectShowWrapper/Movie.h"
#pragma comment(lib,"winmm.lib")
#define CURRWIDTH 1024
#define CURRHEIGHT 768
/*#define CURRWIDTH 1920
#define CURRHEIGHT 1080
#define CURRWIDTH 1600
#define CURRHEIGHT 900*/
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

static Vertex ver24aaRev[] =
{
	{ {-1.0f, 1.0f, -1.0f}, {0.0f, -1.0f, 0.0f} ,{0.0f,0.0f}},
	{ {1.0f, 1.0f, -1.0f}, {0.0f, -1.0f, 0.0f} ,{1.0f,0.0f}},
	{ {1.0f, 1.0f, 1.0f}, {0.0f, -1.0f, 0.0f} ,{1.0f,1.0f}},
	{ {-1.0f, 1.0f, 1.0f}, {0.0f, -1.0f, 0.0f},{0.0f,1.0f} },

	{ {-1.0f, -1.0f, -1.0f}, {0.0f, 1.0f, 0.0f},{0.0f,0.0f} },
	{ {1.0f, -1.0f, -1.0f}, {0.0f, 1.0f, 0.0f} ,{1.0f,0.0f}},
	{ {1.0f, -1.0f, 1.0f}, {0.0f, 1.0f, 0.0f} ,{1.0f,1.0f}},
	{ {-1.0f, -1.0f, 1.0f}, {0.0f, 1.0f, 0.0f} ,{0.0f,1.0f}},

	{ {-1.0f, -1.0f, 1.0f}, {1.0f, 0.0f, 0.0f} ,{0.0f,0.0f}},
	{ {-1.0f, -1.0f, -1.0f}, {1.0f, 0.0f, 0.0f} ,{1.0f,0.0f}},
	{ {-1.0f, 1.0f, -1.0f}, {1.0f, 0.0f, 0.0f} ,{1.0f,1.0f}},
	{ {-1.0f, 1.0f, 1.0f}, {1.0f, 0.0f, 0.0f} ,{0.0f,1.0f}},

	{ {1.0f, -1.0f, 1.0f}, {-1.0f, 0.0f, 0.0f} ,{0.0f,0.0f}},
	{ {1.0f, -1.0f, -1.0f}, {-1.0f, 0.0f, 0.0f} ,{1.0f,0.0f}},
	{ {1.0f, 1.0f, -1.0f}, {-1.0f, 0.0f, 0.0f} ,{1.0f,1.0f}},
	{ {1.0f, 1.0f, 1.0f}, {-1.0f, 0.0f, 0.0f} ,{0.0f,1.0f}},

	{ {-1.0f, -1.0f, -1.0f}, {0.0f, 0.0f, 1.0f} ,{0.0f,0.0f}},
	{ {1.0f, -1.0f, -1.0f}, {0.0f, 0.0f, 1.0f} ,{1.0f,0.0f}},
	{ {1.0f, 1.0f, -1.0f}, {0.0f, 0.0f, 1.0f} ,{1.0f,1.0f}},
	{ {-1.0f, 1.0f, -1.0f}, {0.0f, 0.0f, 1.0f} ,{0.0f,1.0f}},

	{ {-1.0f, -1.0f, 1.0f}, {0.0f, 0.0f, -1.0f} ,{0.0f,0.0f}},
	{ {1.0f, -1.0f, 1.0f}, {0.0f, 0.0f, -1.0f} ,{1.0f,0.0f}},
	{ {1.0f, 1.0f, 1.0f}, {0.0f, 0.0f, -1.0f} ,{1.0f,1.0f}},
	{ {-1.0f, 1.0f, 1.0f}, {0.0f, 0.0f, -1.0f} ,{0.0f,1.0f}},
};

static UINT index36Rev[] =
{
	1,3,0,
	1,2,3,

	4,6,5,
	4,7,6,

	9,11,8,
	9,10,11,

	12,14,13,
	12,15,14,

	17,19,16,
	17,18,19,

	20,22,21,
	20,23,22
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
	dx->setGlobalAmbientLight(0.0f, 0.0f, 0.0f);

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
	const int numPolygon = 4;
	PolygonData pd[numPolygon];
	SkinMesh* sk = new SkinMesh();
	SkinMesh* sk1 = new SkinMesh();
	MeshData* md = new MeshData();
	Wave wav;
	ParticleData* p = new ParticleData();
	ParticleData* bil = new ParticleData();
	PolygonData gr;
	Movie* mov = new Movie("tex/torch1.avi");
	PostEffect blur, mosa;
	PolygonData soto;

	p->GetBufferParticle(dx->GetTexNumber("boss_magic.png"), 0.1f, 5.0f);
	bil->GetBufferBill(2);
	bil->SetVertex(0, { 7,0,7 }, { 0,0,0 });
	bil->SetVertex(1, { -50,0,18 }, { 0,0,0 });
	bil->TextureInit(256, 256);

	wav.SetCommandList(0);
	wav.GetVBarray();
	wav.SetVertex(ver24aa, 24, &index36[30], 6);

	gr.GetVBarray(CONTROL_POINT);
	gr.setVertex(ver24aa, 24, &index36[30], 6);

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

	pd[0].setVertex(ver24aa, sizeof(ver24aa) / sizeof(Vertex), index36, sizeof(index36) / sizeof(UINT));
	pd[1].setVertex(ver24aa, sizeof(ver24aa) / sizeof(Vertex), index36, sizeof(index36) / sizeof(UINT));
	pd[2].setVertex(ver24aa, sizeof(ver24aa) / sizeof(Vertex), index36, sizeof(index36) / sizeof(UINT));
	pd[3].setVertex(ver24aa, sizeof(ver24aa) / sizeof(Vertex), index36, sizeof(index36) / sizeof(UINT));

	soto.GetVBarray(SQUARE);
	soto.setVertex(ver24aaRev, sizeof(ver24aaRev) / sizeof(Vertex), index36Rev, sizeof(index36Rev) / sizeof(UINT));

	dx->Bigin(0);
	blur.ComCreateBlur();
	mosa.ComCreateMosaic();
	p->CreateParticle(dx->GetTexNumber("leaf.png"));
	bil->CreateBillboard();
	DivideArr arr[3];
	arr[0].distance = 90.0f;
	arr[0].divide = 2;//頂点数 3 → 3 * 6 = 18
	arr[1].distance = 50.0f;
	arr[1].divide = 48;//頂点数 3 → 3 * 3456 = 10368
	arr[2].distance = 36.0f;
	arr[2].divide = 96;//頂点数 3 → 3 * 13824 = 41472
	DivideArr arrsk[3];
	arrsk[0].distance = 90.0f;
	arrsk[0].divide = 2;//頂点数 3 → 3 * 6 = 18
	arrsk[1].distance = 50.0f;
	arrsk[1].divide = 6;
	arrsk[2].distance = 36.0f;
	arrsk[2].divide = 12;
	md->setDivideArr(arrsk, 3);
	sk->setDivideArr(arrsk, 3);
	//dx->wireFrameTest(true);
	md->CreateMesh();
	sk->CreateFromFBX();
	sk->setInternalAnimationIndex(0);
	sk1->CreateFromFBX();
	sk1->setInternalAnimationIndex(0);
	wav.Create(dx->GetTexNumber("wave.jpg"), -1, TRUE, TRUE, 0.04f, 64.0f);

	gr.setDivideArr(arr, 3);
	gr.Create(true, dx->GetTexNumber("ground3.jpg"),
		dx->GetTexNumber("ground3Nor.png"),
		dx->GetTexNumber("ground3.jpg"), true, true);

	pd[0].setDivideArr(arr, 3);

	pd[0].Create(true, dx->GetTexNumber("wall1.jpg"),
		dx->GetTexNumber("wall1Nor.png"),
		dx->GetTexNumber("wall1.jpg"), true, true);
	pd[1].Create(true, dx->GetTexNumber("ceiling5.jpg"), /*dx->GetTexNumber("ceiling5Nor.png")*/-1, -1, true, true);
	pd[2].Create(true, dx->GetTexNumber("siro.png"), -1, -1, true, true);
	pd[3].Create(true, dx->GetTexNumber("boss_magic.png"), -1, -1, true, true);

	soto.Create(true, dx->GetTexNumber("wall1.jpg"),
		dx->GetTexNumber("wall1Nor.png"),
		dx->GetTexNumber("wall1.jpg"), true, true);

	dx->End(0);
	dx->WaitFence();
	int numMesh = sk->getNumMesh();
	int numMesh1 = sk1->getNumMesh();
	UINT numMT = numPolygon + numMesh + numMesh1 + 6 + 1;
	MaterialType* type = new MaterialType[numMT];

	type[0] = NONREFLECTION;
	type[1] = METALLIC;
	type[2] = EMISSIVE;
	type[3] = METALLIC;
	for (int i = numPolygon; i < numMesh + numPolygon; i++)type[i] = NONREFLECTION;
	for (int i = numMesh + numPolygon; i < numMesh + numPolygon + numMesh1; i++)type[i] = NONREFLECTION;
	type[numMesh + numPolygon + numMesh1] = NONREFLECTION;
	type[numMesh + numPolygon + numMesh1 + 1] = NONREFLECTION;
	type[numMesh + numPolygon + numMesh1 + 2] = METALLIC;
	type[numMesh + numPolygon + numMesh1 + 3] = EMISSIVE;
	type[numMesh + numPolygon + numMesh1 + 4] = EMISSIVE;
	type[numMesh + numPolygon + numMesh1 + 5] = NONREFLECTION;
	type[numMesh + numPolygon + numMesh1 + 6] = DIRECTIONLIGHT_NONREFLECTION;
	//type[numMesh + numPolygon + numMesh1 + 6] = NONREFLECTION;
	ParameterDXR** pdx = new ParameterDXR * [numMT - 1];
	for (int i = 0; i < numPolygon; i++)
		pdx[i] = pd[i].getParameter();
	for (int i = numPolygon; i < numMesh + numPolygon; i++)
		pdx[i] = sk->getParameter(i - numPolygon);
	for (int i = numMesh + numPolygon; i < numMesh + numPolygon + numMesh1; i++)
		pdx[i] = sk1->getParameter(i - (numMesh + numPolygon));
	pdx[numMesh + numPolygon + numMesh1] = md->getParameter();
	pdx[numMesh + numPolygon + numMesh1 + 1] = wav.getParameter();
	pdx[numMesh + numPolygon + numMesh1 + 2] = bil->getParameter();
	pdx[numMesh + numPolygon + numMesh1 + 3] = p->getParameter();
	pdx[numMesh + numPolygon + numMesh1 + 4] = gr.getParameter();
	pdx[numMesh + numPolygon + numMesh1 + 5] = soto.getParameter();
	dxr.initDXR(0, numMT - 1, pdx, type, 5);
	float theta = 0;
	float thetaO = 0;
	float camTheta = 0;
	int insCnt = 0;
	bool rayF = false;
	bool eff[2];
	eff[0] = false;
	eff[1] = false;
	T_float tfloat;
	int parCnt = 0;
	bool parSwich = false;
	bool plight = true;
	bool plight2 = true;
	bool dlight = true;
	while (1) {
		if (!DispatchMSG(&msg)) {
			break;
		}
		T_float::GetTime(hWnd);
		T_float::GetTimeUp(hWnd);

		Directionkey key = con->Direction();
		if (key == LEFT)rayF = !rayF;//レイトレ
		if (key == UP)eff[0] = !eff[0];
		if (key == DOWN)eff[1] = !eff[1];//モザイク
		if (key == ENTER)plight = !plight;//Ctrl
		if (key == CANCEL)dlight = !dlight;//Delete
		if (key == RIGHT)plight2 = !plight2;

		float th = tfloat.Add(0.15f);
		float th1 = tfloat.Add(0.05f);
		float ca = tfloat.Add(0.1f);
		theta = theta += th;
		if (theta > 360)theta = 0;
		thetaO = thetaO += th1;
		if (thetaO > 360)thetaO = 0;
		MATRIX thetaZ;
		VECTOR3 light1 = { 0, -40, 15 };
		VECTOR3 light2 = { 0,50,-30 };
		MatrixRotationZ(&thetaZ, 360-theta);
		VectorMatrixMultiply(&light1, &thetaZ);
		VectorMatrixMultiply(&light2, &thetaZ);

		insCnt++;
		if (insCnt > 600) {
			insCnt = 0;
		}

		dx->SetDirectionLight(dlight);
		dx->DirectionLight(0.4f, 0.4f, -1.0f, 0.4f, 0.3f, 0.3f);

		dx->PointLightPosSet(0,
			{ light1.x, light1.y, light1.z },
			{ 1, 1, 1, 1 }, plight, 1000);
		dx->PointLightPosSet(1,
			{ 14, 0, 5 },
			{ 1, 1, 1, 1 }, plight2, 500, { 0.1f,0.01f,0.01f });
		dx->PointLightPosSet(2,
			{ -14, 0, 5 },
			{ 1, 1, 1, 1 }, plight2, 500, { 1.1f ,0.01f,0.01f });
		dx->PointLightPosSet(3,
			{ 0, 0, 0 },
			{ 1, 1, 1, 1 }, false, 10);

		camTheta = camTheta += ca;
		if (camTheta > 360)camTheta = 0;
		MATRIX camThetaZ;
		VECTOR3 cam1 = { 0, -70, 20 };
		MatrixRotationZ(&camThetaZ, camTheta);
		VectorMatrixMultiply(&cam1, &camThetaZ);
		dx->Cameraset({ cam1.x, cam1.y, cam1.z }, { 0, 0, 0 });

		pd[0].Instancing({ 35, 0, 0 },
			{ 0, 0, 0 },
			{ 7, 7, 7 });

		pd[0].InstancingUpdate({ 0, 0, 0, 0 },
			1,
			4.0f);

		pd[1].Instancing({ -35, 0, 0 },
			{ 0, 0, 0 },
			{ 7, 7, 7 });

		pd[1].InstancingUpdate({ 0, 0, 0, 0 },
			0,
			4.0f);

		pd[2].Instancing({ light1.x, light1.y, light1.z },
			{ 0, 0, 0 },
			{ 1, 1, 1 });
		pd[2].InstancingUpdate({ 0, 0, 0, 0 },
			0,
			4.0f);

		pd[3].Instancing({ 0, 0, 15 },
			{ 0, 0, thetaO },
			{ 4, 4, 4 });
		pd[3].InstancingUpdate({ 0, 0, 0, 0 },
			0,
			4.0f);

		float m = tfloat.Add(2.0f);

		sk->Update(0, m,
			{ 15, 0, 0 },
			{ 0, 0, 0, 0 },
			{ 0, 0, 0 },
			{ 1.2f,1.2f,1.2f });
		sk1->Update(0, m,
			{ -15, 0, 0 },
			{ 0, 0, 0, 0 },
			{ 0, 0, 0 },
			{ 1.2f,1.2f,1.2f });

		md->Update({ 0, 0, -10 },
			{ 0, 0, 0, 0 },
			{ 0, 0, 0 },
			{ 1,1,1 },
			1);

		float m2 = tfloat.Add(0.003f);
		wav.Instancing(m2, { 0, 0, -20 },
			{ 0,0,0 },
			{ 60, 60, 15 });
		wav.InstancingUpdate({ 0, 0, 0, -0.1f },
			0.0000f, 4.0f);

		gr.Instancing({ 0, 0, -28 },
			{ 0, 0, 0 },
			{ 60, 60, 15 });

		gr.InstancingUpdate({ 0, 0, 0, 0 },
			0.01f,
			1.0f);

		soto.Instancing({ 0, 0, 0 },
			{ 0, 0, 0 },
			{ 60, 60, 60 });
		soto.InstancingUpdate({ 0, 0, 0, 0 },
			0,
			4.0f);

		float sp1 = tfloat.Add(0.03f);
		parCnt += sp1;
		if (parCnt > 3) {
			parCnt = 0; parSwich = true;
		}
		float sp = tfloat.Add(0.03f);
		p->Update({ 0,0,5 }, { 0,0,0 }, 0, 0.1f, parSwich, sp);
		parSwich = false;
		bil->Update(10.0f, { 0,0,0,-0.3f });
		if (!rayF)
			text->UpDateText(L"レイトレオフ", 185.0f, 30.0f, 30.0f, { 1.0f, 1.0f, 1.0f, 1.0f });
		else
			text->UpDateText(L"レイトレオン", 185.0f, 30.0f, 30.0f, { 1.0f, 0.0f, 0.0f, 1.0f });
		if (!eff[1])
			text->UpDateText(L"モザイクオフ", 185.0f, 60.0f, 30.0f, { 1.0f, 1.0f, 1.0f, 1.0f });
		else
			text->UpDateText(L"モザイクオン", 185.0f, 60.0f, 30.0f, { 1.0f, 0.0f, 0.0f, 1.0f });
		text->UpDate();

		if (!rayF) {
			dx->Bigin(0);
			dx->BiginDraw(0);
			soto.Draw();
			p->Draw();
			sk1->Draw();
			pd[0].Draw();
			pd[1].Draw();
			pd[2].Draw();
			pd[3].Draw();
			md->Draw();
			gr.Draw();
			wav.Draw();
			sk->Draw();
			bil->SetTextureMPixel(mov->GetFrame(256, 256, 50));
			bil->DrawBillboard();
			if (eff[0])blur.ComputeBlur(true, 400, 300, 200);
			else blur.ComputeBlur(false, 400, 300, 200);
			if (eff[1])mosa.ComputeMosaic(true, 10);
			else mosa.ComputeMosaic(false, 10);
			text->Draw(0);
			dx->EndDraw(0);
			dx->End(0);
			dx->WaitFence();
		}
		else {
			soto.StreamOutput();
			sk->StreamOutput();
			sk1->StreamOutput();
			pd[0].StreamOutput();
			pd[1].StreamOutput();
			pd[2].StreamOutput();
			pd[3].StreamOutput();
			md->StreamOutput();
			gr.StreamOutput();
			wav.StreamOutput();
			p->StreamOutput();
			dx->Bigin(0);
			bil->SetTextureMPixel(mov->GetFrame(256, 256, 50));
			dx->End(0);
			dx->WaitFence();
			bil->StreamOutputBillboard();
			dx->Bigin(0);
			dxr.raytrace(0, 5);
			dx->End(0);
			dx->WaitFence();

			dx->Bigin(0);
			dx->BiginDraw(0, false);
			if (eff[0])blur.ComputeBlur(true, 400, 300, 200);
			else blur.ComputeBlur(false, 400, 300, 200);
			if (eff[1])mosa.ComputeMosaic(true, 10);
			else mosa.ComputeMosaic(false, 10);
			text->Draw(0);
			dx->EndDraw(0);
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
	S_DELETE(p);
	S_DELETE(bil);
	S_DELETE(mov);
	Control::DeleteInstance();
	DxText::DeleteInstance();
	Dx12Process::DeleteInstance();
	return 0;
}