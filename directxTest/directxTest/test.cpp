
//////////////////////////////////////DirectXテスト/////////////////////////////////////////////////////////////

#include"../../../Common/Direct3DWrapper/Dx12Process.h"
#include"../../../Common/Direct3DWrapper/DxText.h"
#include"../../../Common/Window/Win.h"
#include"../../../JPGLoader/JPGLoader.h"
#include"../../../PNGLoader/PNGLoader.h"
#include"../../../Common/SearchFile/SearchFile.h"
#include"../../../Common/DirectShowWrapper/Movie.h"
#include"../../../MultiThread/MultiThread.h"
#pragma comment(lib,"winmm.lib")
#include <Process.h>
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

void update();
void draw();
void AS();
void raytrace();
const int numPolygon = 4;
float theta = 0;
float thetaO = 0;
float camTheta = 0;
int insCnt = 0;
bool rayF = false;
bool eff[2];
T_float tfloat;
int parCnt = 0;
bool parSwich = false;
bool plight = true;
bool plight2 = true;
bool dlight = true;
//ウィンドウハンドル
HWND hWnd;
MSG msg;
Dx12Process* dx;
DxText* text;
DXR_Basic* dxr;
PolygonData* pd;
SkinMesh* sk;
SkinMesh* sk1;
MeshData* md;
Wave* wav;
ParticleData* p;
ParticleData* bil;
PolygonData* gr;
Movie* mov;
PostEffect* blur, * mosa;
PolygonData* soto;
Control* con;
int sync[3] = {};

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) {

	srand((unsigned)time(NULL));

	if (Createwindow(&hWnd, hInstance, nCmdShow, CURRWIDTH, CURRHEIGHT, L"DirectX_Test") == -1)return FALSE;

	//DirectX12ラッパー
	Dx12Process::InstanceCreate();
	dx = Dx12Process::GetInstance();
	con = Control::GetInstance();
	dxr = new DXR_Basic();
	dx->dxrCreateResource();
	dx->Initialize(hWnd, CURRWIDTH, CURRHEIGHT);
	dx->setGlobalAmbientLight(0.0f, 0.0f, 0.0f);

	SearchFile* sf = new SearchFile(2);
	char** strE = new char* [2];
	strE[0] = "jpg";
	strE[1] = "png";
	sf->Search(L"./tex/*", 0, strE, 2);
	sf->Search(L"../../../Black Dragon NEW/textures/*", 1, strE, 2);
	UINT numFile1 = sf->GetFileNum(0);
	UINT numFile2 = sf->GetFileNum(1);
	JPGLoader jpg;
	PNGLoader png;
	UINT resCnt = 0;
	ARR_DELETE(strE);
	for (int k = 0; k < 2; k++) {
		for (int i = 0; i < sf->GetFileNum(k); i++) {
			char* str = sf->GetFileName(k, i);
			UCHAR* byte = jpg.loadJPG(str, 0, 0, nullptr);
			unsigned int w = jpg.getSrcWidth();
			unsigned int h = jpg.getSrcHeight();
			if (byte == nullptr) {
				byte = png.loadPNG(str, 0, 0, nullptr);
				w = png.getSrcWidth();
				h = png.getSrcHeight();
			}

			dx->createTextureArr(numFile1 + numFile2, resCnt++, dx->GetNameFromPass(str),
				byte, DXGI_FORMAT_R8G8B8A8_UNORM,
				w, w * 4, h);
			if (w < 10 || h < 10) {
				int b = 0;
			}
			ARR_DELETE(byte);
		}
	}

	//文字入力
	DxText::InstanceCreate();
	text = DxText::GetInstance();
	pd = new PolygonData[numPolygon];
	sk = new SkinMesh();
	sk1 = new SkinMesh();
	md = new MeshData();
	p = new ParticleData();
	bil = new ParticleData();
	mov = new Movie("tex/torch1.avi");
	wav = new Wave();
	blur = new PostEffect();
	mosa = new PostEffect();
	soto = new PolygonData();
	gr = new PolygonData();

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
	sk1->setDivideArr(arrsk, 3);
	gr->setDivideArr(arr, 3);
	pd[0].setDivideArr(arr, 3);

	p->GetBufferParticle(dx->GetTexNumber("boss_magic.png"), 0.1f, 5.0f);
	bil->GetBufferBill(2);
	bil->SetVertex(0, { 0,50,7 }, { 0,0,0 });
	bil->SetVertex(1, { 0,-50,18 }, { 0,0,0 });
	bil->TextureInit(256, 256);

	wav->SetCommandList(0);
	wav->GetVBarray(1);
	wav->SetVertex(ver24aa, 24, &index36[30], 6);

	gr->GetVBarray(CONTROL_POINT, 1);
	gr->setVertex(ver24aa, 24, &index36[30], 6);

	md->SetCommandList(0);
	md->SetState(TRUE, TRUE, false);
	md->GetBuffer("mesh/tree.obj", 2);
	md->SetVertex();

	sk->SetCommandList(0);
	sk->SetState(true, true);
	sk->ObjOffset(0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0);
	sk->GetFbx("mesh/player2_fbx_att.fbx");
	//HRESULT hr = sk->GetFbx("../../../Black Dragon NEW/Dragon_Baked_Actions_fbx_7.4_binary.fbx");
	sk->GetBuffer(3200.0f);
	sk->SetVertex();

	sk1->SetCommandList(0);
	sk1->SetState(true, true);
	sk1->ObjOffset(0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0);
	sk1->GetFbx("mesh/player1_fbx_att.fbx");
	sk1->GetBuffer(2900.0f);
	sk1->SetVertex();

	pd[0].GetVBarray(CONTROL_POINT, 2);
	pd[1].GetVBarray(SQUARE, 2);
	pd[2].GetVBarray(SQUARE, 1);
	pd[3].GetVBarray(SQUARE, 1);

	pd[0].setVertex(ver24aa, sizeof(ver24aa) / sizeof(Vertex), index36, sizeof(index36) / sizeof(UINT));
	pd[1].setVertex(ver24aa, sizeof(ver24aa) / sizeof(Vertex), index36, sizeof(index36) / sizeof(UINT));
	pd[2].setVertex(ver24aa, sizeof(ver24aa) / sizeof(Vertex), index36, sizeof(index36) / sizeof(UINT));
	pd[3].setVertex(ver24aa, sizeof(ver24aa) / sizeof(Vertex), index36, sizeof(index36) / sizeof(UINT));

	soto->GetVBarray(SQUARE, 1);
	soto->setVertex(ver24aaRev, sizeof(ver24aaRev) / sizeof(Vertex), index36Rev, sizeof(index36Rev) / sizeof(UINT));

	dx->Bigin(0);
	blur->ComCreateBlur();
	mosa->ComCreateMosaic();
	p->CreateParticle(dx->GetTexNumber("leaf.png"));
	bil->CreateBillboard();
	//dx->wireFrameTest(true);
	md->CreateMesh();
	sk1->CreateFromFBX();
	bool a = sk->CreateFromFBX();
	sk->setInternalAnimationIndex(0);

	sk1->setInternalAnimationIndex(0);
	wav->Create(dx->GetTexNumber("wave.jpg"), -1, TRUE, TRUE, 0.04f, 64.0f);

	gr->Create(true, dx->GetTexNumber("ground3.jpg"),
		dx->GetTexNumber("ground3Nor.png"),
		dx->GetTexNumber("ground3.jpg"), true, true);

	pd[0].Create(true, dx->GetTexNumber("wall1.jpg"),
		dx->GetTexNumber("wall1Nor.png"),
		dx->GetTexNumber("wall1.jpg"), true, true);
	pd[1].Create(true, dx->GetTexNumber("ceiling5.jpg"), /*dx->GetTexNumber("ceiling5Nor.png")*/-1, -1, true, true);
	pd[2].Create(true, dx->GetTexNumber("siro.png"), -1, -1, true, true);
	pd[3].Create(true, dx->GetTexNumber("boss_magic.png"), -1, -1, true, true);

	soto->Create(true, dx->GetTexNumber("wall1.jpg"),
		dx->GetTexNumber("wall1Nor.png"),
		dx->GetTexNumber("wall1.jpg"), true, true);

	dx->End(0);
	dx->WaitFence();
	int numMesh = sk->getNumMesh();
	int numMesh1 = sk1->getNumMesh();
	int numMaterial = 0;
	int numMaterial1 = 0;
	UINT numMT = numPolygon + numMesh + numMesh1 + 6;

	ParameterDXR** pdx = new ParameterDXR * [numMT];
	for (int i = 0; i < numPolygon; i++)
		pdx[i] = pd[i].getParameter();
	for (int i = numPolygon; i < numMesh + numPolygon; i++) {
		pdx[i] = sk->getParameter(i - numPolygon);
		numMaterial += pdx[i]->NumMaterial;
	}
	for (int i = numMesh + numPolygon; i < numMesh + numPolygon + numMesh1; i++) {
		pdx[i] = sk1->getParameter(i - (numMesh + numPolygon));
		numMaterial1 += pdx[i]->NumMaterial;
	}
	pdx[numMesh + numPolygon + numMesh1] = md->getParameter();
	pdx[numMesh + numPolygon + numMesh1 + 1] = wav->getParameter();
	pdx[numMesh + numPolygon + numMesh1 + 2] = bil->getParameter();
	pdx[numMesh + numPolygon + numMesh1 + 3] = p->getParameter();
	pdx[numMesh + numPolygon + numMesh1 + 4] = gr->getParameter();
	pdx[numMesh + numPolygon + numMesh1 + 5] = soto->getParameter();

	UINT numMT1 = numPolygon + numMaterial + numMaterial1 + 6 + 1;
	MaterialType* type = new MaterialType[numMT1];

	type[0] = NONREFLECTION;
	type[1] = METALLIC;
	type[2] = EMISSIVE;
	type[3] = METALLIC;
	for (int i = numPolygon; i < numMaterial + numPolygon; i++)type[i] = NONREFLECTION;
	for (int i = numMaterial + numPolygon; i < numMaterial + numPolygon + numMaterial1; i++)type[i] = NONREFLECTION;
	type[numMaterial + numPolygon + numMaterial1] = NONREFLECTION;
	type[numMaterial + numPolygon + numMaterial1 + 1] = NONREFLECTION;
	type[numMaterial + numPolygon + numMaterial1 + 2] = METALLIC;
	type[numMaterial + numPolygon + numMaterial1 + 3] = EMISSIVE;
	type[numMaterial + numPolygon + numMaterial1 + 4] = EMISSIVE;
	type[numMaterial + numPolygon + numMaterial1 + 5] = NONREFLECTION;
	type[numMaterial + numPolygon + numMaterial1 + 6] = DIRECTIONLIGHT_NONREFLECTION;
	//type[numMaterial + numPolygon + numMaterial1 + 6] = NONREFLECTION;


	dxr->initDXR(numMT, pdx, type, 3);
	eff[0] = false;
	eff[1] = false;
	MultiThread th;
	th.setFunc(update);
	th.setFunc(draw);
	th.setFunc(AS);
	th.setFunc(raytrace);
	th.start();
	while (1) {
		if (!DispatchMSG(&msg)) {
			break;
		}
		T_float::GetTime(hWnd);
		T_float::GetTimeUp(hWnd);
		float ca = tfloat.Add(0.1f);
		camTheta = camTheta += ca;
		if (camTheta > 360)camTheta = 0;
		MATRIX camThetaZ;
		VECTOR3 cam1 = { 0, -70, 10 };
		MatrixRotationZ(&camThetaZ, camTheta);
		VectorMatrixMultiply(&cam1, &camThetaZ);
		dx->Cameraset({ cam1.x, cam1.y, cam1.z }, { 0, 0, 0 });

		dx->Bigin(0);
		bil->SetTextureMPixel(mov->GetFrame(256, 256, 50));
		dx->End(0);
		dx->WaitFence();

		sync[0] = 1 - sync[0];
		sync[1] = 1 - sync[1];
		sync[2] = 1 - sync[2];
		dx->setUpSwapIndex(sync[0]);
		dx->setDrawSwapIndex(1 - sync[0]);
		dx->setStreamOutputSwapIndex(sync[1]);
		dx->setRaytraceSwapIndex(1 - sync[1]);
		dxr->setASswapIndex(sync[2]);
		dxr->setRaytraceSwapIndex(1 - sync[2]);

		th.wait();

		dx->Bigin(0);
		dx->BiginDraw(0, false);
		if (eff[0])blur->ComputeBlur(0, true, 400, 300, 200);
		else blur->ComputeBlur(0, false, 400, 300, 200);
		if (eff[1])mosa->ComputeMosaic(0, true, 10);
		else mosa->ComputeMosaic(0, false, 10);
		text->Draw(0);
		dx->EndDraw(0);
		dx->End(0);
		dx->WaitFence();
		dx->DrawScreen();
	}
	th.end();

	ARR_DELETE(pd);
	ARR_DELETE(type);
	ARR_DELETE(pdx);
	S_DELETE(gr);
	S_DELETE(sk);
	S_DELETE(sk1);
	S_DELETE(sf);
	S_DELETE(md);
	S_DELETE(p);
	S_DELETE(bil);
	S_DELETE(mov);
	S_DELETE(wav);
	S_DELETE(blur);
	S_DELETE(mosa);
	S_DELETE(soto);
	S_DELETE(dxr);
	Control::DeleteInstance();
	DxText::DeleteInstance();
	Dx12Process::DeleteInstance();
	return 0;
}

static bool d = true;

void update() {
	Directionkey key = con->Direction();
	if (key == LEFT)rayF = !rayF;//レイトレ
	if (key == UP)d = !d;
	if (key == DOWN)eff[1] = !eff[1];//モザイク
	if (key == ENTER)plight = !plight;//Ctrl
	if (key == CANCEL)dlight = !dlight;//Delete
	if (key == RIGHT)plight2 = !plight2;

	dx->SetDirectionLight(dlight);
	dx->DirectionLight(0.4f, 0.4f, -1.0f, 0.4f, 0.3f, 0.3f);
	float th = tfloat.Add(0.15f);
	theta = theta += th;
	if (theta > 360)theta = 0;
	MATRIX thetaZ;
	VECTOR3 light1 = { 0, -40, 15 };
	VECTOR3 light2 = { 0,50,-30 };
	MatrixRotationZ(&thetaZ, 360 - theta);
	VectorMatrixMultiply(&light1, &thetaZ);
	VectorMatrixMultiply(&light2, &thetaZ);

	dx->PointLightPosSet(0,
		{ light1.x, light1.y, light1.z },
		{ 1, 1, 1, 1 }, plight, 1000, { 0.01f,0.001f,0.001f });
	dx->PointLightPosSet(1,
		{ 14, 0, 5 },
		{ 1, 1, 1, 1 }, plight2, 1000, { 0.01f,0.001f,0.001f });
	dx->PointLightPosSet(2,
		{ -14, 0, 5 },
		{ 1, 1, 1, 1 }, plight2, 1000, { 0.01f,0.001f,0.001f });
	dx->PointLightPosSet(3,
		{ 0, 0, 0 },
		{ 1, 1, 1, 1 }, true, 10);

	float th1 = tfloat.Add(0.05f);

	thetaO = thetaO += th1;
	if (thetaO > 360)thetaO = 0;

	insCnt++;
	if (insCnt > 1100) {
		insCnt = 0;
	}


	for (int b = 0; b < 2; b++) {
		if (insCnt > b * 100)
			pd[0].Instancing({ (float)35 - (b * 10), 0, 20 },
				{ 0, 0, 0 },
				{ 7, 7, 7 });
	}

	pd[0].InstancingUpdate({ 0, 0, 0, 0 },
		1,
		4.0f);

	for (int b = 0; b < 2; b++) {
		if (insCnt > b * 100)
			pd[1].Instancing({ (float)-35 + (b * 10), 0, 10 },
				{ 0, 0, 0 },
				{ 7, 7, 7 });
	}
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

	if (d) {
		/*sk->Update(0, m,
			{ 0, 0, 0 },
			{ 0, 0, 0, 0 },
			{ 90, 0, 0 },
			{ 0.005f,0.005f,0.005f });*/

		sk->Update(0, m,
			{ 15, 0, 0 },
			{ 0, 0, 0, 0 },
			{ 0, 0, 0 },
			{ 1.2f,1.2f,1.2f });
	}
	else sk->DrawOff();

	sk1->Update(0, m,
		{ -15, 0, 0 },
		{ 0, 0, 0, 0 },
		{ 0, 0, theta },
		{ 1.2f,1.2f,1.2f });

	md->Instancing({ 0, 0, -10 },
		{ 0, 0, 0},
		{ 1,1,1 });
	md->Instancing({ 0, 0, 30 },
		{ 0, 0, 0 },
		{ 1,1,1 });
	md->InstancingUpdate(
		{ 0, 0, 0, 0 },0,4.0);

	float m2 = tfloat.Add(0.003f);
	wav->Instancing(m2, { 0, 0, -20 },
		{ 0,0,0 },
		{ 60, 60, 15 });
	wav->InstancingUpdate({ 0, 0, 0, -0.1f },
		0.0000f, 4.0f);

	gr->Instancing({ 0, 0, -28 },
		{ 0, 0, 0 },
		{ 60, 60, 15 });

	gr->InstancingUpdate({ 0, 0, 0, 0 },
		0.01f,
		1.0f);

	soto->Instancing({ 0, 0, 0 },
		{ 0, 0, 0 },
		{ 60, 60, 60 });
	soto->InstancingUpdate({ 0, 0, 0, 0 },
		0,
		4.0f);

	float sp1 = tfloat.Add(0.03f);
	parCnt += sp1;
	if (parCnt > 3) {
		parCnt = 0; parSwich = true;
	}
	float sp = tfloat.Add(0.03f);
	if (d) {
		p->Update({ 0,0,5 }, { 0,0,0 }, 0, 0.1f, parSwich, sp);
		parSwich = false;
		bil->Update(10.0f, { 0,0,0,-0.3f });
	}
	else {
		p->DrawOff();
		bil->DrawOff();
	}
	if (!rayF)
		text->UpDateText(L"レイトレオフ", 185.0f, 30.0f, 30.0f, { 1.0f, 1.0f, 1.0f, 1.0f });
	else
		text->UpDateText(L"レイトレオン", 185.0f, 30.0f, 30.0f, { 1.0f, 0.0f, 0.0f, 1.0f });
	if (!eff[1])
		text->UpDateText(L"モザイクオフ", 185.0f, 60.0f, 30.0f, { 1.0f, 1.0f, 1.0f, 1.0f });
	else
		text->UpDateText(L"モザイクオン", 185.0f, 60.0f, 30.0f, { 1.0f, 0.0f, 0.0f, 1.0f });
	text->UpDate();
}

void draw() {
	int com = 1;
	if (!rayF) {
		dx->Bigin(com);
		dx->BiginDraw(com);
		soto->Draw(com);
		p->Draw(com);
		sk1->Draw(com);
		pd[0].Draw(com);
		pd[1].Draw(com);
		pd[2].Draw(com);
		pd[3].Draw(com);
		md->Draw(com);
		gr->Draw(com);
		wav->Draw(com);
		sk->Draw(com);
		bil->DrawBillboard(com);
		dx->EndDraw(com);
		dx->End(com);
		dx->WaitFence();
	}
	else {
		dx->Bigin(com);
		sk->StreamOutput(com);//update
		sk1->StreamOutput(com);//update
		p->StreamOutput(com);//update
		bil->StreamOutputBillboard(com);//update
		soto->StreamOutput(com);
		pd[0].StreamOutput(com);//update
		pd[1].StreamOutput(com);
		pd[2].StreamOutput(com);
		pd[3].StreamOutput(com);
		md->StreamOutput(com);
		gr->StreamOutput(com);//update
		wav->StreamOutput(com);//update
		dx->End(com);
		dx->WaitFence();

		sk->UpdateDxrDivideBuffer();
		sk1->UpdateDxrDivideBuffer();
		pd[0].UpdateDxrDivideBuffer();
		wav->UpdateDxrDivideBuffer();
		gr->UpdateDxrDivideBuffer();
	}
}

void AS() {
	int com = 2;
	if (rayF) {
		dx->BiginCom(com);
		dxr->update_c(com, 3);
		dx->EndCom(com);
		dx->WaitFenceCom();
	}
}

void raytrace() {
	int com = 3;
	if (rayF) {
		dx->Bigin(com);
		dxr->updateVertexBuffer(com);
		dxr->raytrace_g(com);
		dxr->copyBackBuffer(com);
		dxr->copyDepthBuffer(com);
		dx->End(com);
		dx->WaitFence();
	}
}
