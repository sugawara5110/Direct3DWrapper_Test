
//////////////////////////////////////DirectXテスト/////////////////////////////////////////////////////////////

#include"../../../Common/Direct3DWrapper/Dx12Process.h"
#include"../../../Common/Direct3DWrapperOption/DxText.h"
#include"../../../Common/Direct3DWrapperOption/Dx_ParticleData.h"
#include"../../../Common/Direct3DWrapperOption/Dx_PostEffect.h"
#include"../../../Common/Direct3DWrapperOption/Dx_Wave.h"
#include"../../../Common/Window/Win.h"
#include"../../../JPGLoader/JPGLoader.h"
#include"../../../PNGLoader/PNGLoader.h"
#include"../../../Common/SearchFile/SearchFile.h"
#include"../../../Common/DirectShowWrapper/Movie.h"
#include"../../../MultiThread/MultiThread.h"
#include"../../../UserInterface/UserInterface.h"
#include"../../../TIFLoader/TIFLoader.h"
#include"../../../CreateGeometry/CreateGeometry.h"
#include <Process.h>
#define CURRWIDTH 1024
#define CURRHEIGHT 768
//#define CURRWIDTH 1920
//#define CURRHEIGHT 1080
//#define CURRWIDTH 640
//#define CURRHEIGHT 480
/*#define CURRWIDTH 1920
#define CURRHEIGHT 1080
#define CURRWIDTH 1600
#define CURRHEIGHT 900*/
#define _CRT_SECURE_NO_WARNINGS
using namespace CoordTf;
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
void UpdateDxrDivideBuffer();
const int numPolygon = 4;
float theta = 0;
float thetaO = 0;
float camTheta = 0;
int insCnt = 0;
static bool rayF123= false;
bool eff[4];
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
PolygonData* soto;
Movie* mov;
PostEffect* blur, * mosa, * mblur;
Control* con;
UserInterfaceMeter ui;
UserInterfaceWindow wi;

void testDxInput() {
	Dx12Process::InstanceCreate();
	dx = Dx12Process::GetInstance();
	con = Control::GetInstance();
	dx->dxrCreateResource();
	dx->Initialize(hWnd, CURRWIDTH, CURRHEIGHT);
	dx->setGlobalAmbientLight(0.0f, 0.0f, 0.0f);
	DxText::InstanceCreate();
	text = DxText::GetInstance();

	DxInput* di = DxInput::GetInstance();
	di->create(hWnd);
	di->SetWindowMode(true);
	di->setCorrectionX(1.015f);
	di->setCorrectionY(1.055f);
	int keyCnt = 0;
	while (1) {
		T_float::GetTime(hWnd);
		T_float::GetTimeUp(hWnd);
		if (!DispatchMSG(&msg)) {
			break;
		}
		Directionkey key = con->Direction();
		if(key != NOTPRESS)keyCnt++;
		DxText::GetInstance()->UpDateValue(keyCnt, 10, 400, 30.0f, 5, { 0.3f, 1.0f, 0.3f, 1.0f });
		Directionkey key2 = con->Direction();
		int i = key;
		int i2 = key2;
		i = di->checkKeyDownNo();
		i2 = di->checkKeyActionNo();
		DxText::GetInstance()->UpDateValue(i, 400, 400, 30.0f, 5, { 0.3f, 1.0f, 0.3f, 1.0f });
		DxText::GetInstance()->UpDateValue(i2, 400, 450, 30.0f, 5, { 1.0f, 1.0f, 1.0f, 1.0f });
		int m = 0;
		int m2 = 0;
		if (di->isLAction())m = 1;
		if (di->isMAction())m = 2;
		if (di->isRAction())m = 3;
		if (di->isLDown())m2 = 1;
		if (di->isMDown())m2 = 2;
		if (di->isRDown())m2 = 3;
		DxText::GetInstance()->
			UpDateValue(m, di->PosX(), di->PosY(), 30.0f, 1, { 1.0f, 1.0f, 1.0f, 1.0f });
		DxText::GetInstance()->
			UpDateValue(m2, di->PosX(), di->PosY() + 30.0f, 30.0f, 1, { 1.0f, 1.0f, 1.0f, 1.0f });

		DxText::GetInstance()->
			UpDateValue(di->PosX(), 100, 100, 30.0f, 1, { 1.0f, 1.0f, 1.0f, 1.0f });
		DxText::GetInstance()->
			UpDateValue(di->PosY(), 100, 130, 30.0f, 1, { 1.0f, 1.0f, 1.0f, 1.0f });
		DxText::GetInstance()->UpDate();

		dx->Bigin(0);
		dx->BiginDraw(0, true);
		text->Draw(0);
		dx->EndDraw(0);
		dx->End(0);
		dx->RunGpu();
		dx->WaitFence();
		dx->DrawScreen();
		Sleep(30);
	}

	DxInput::DeleteInstance();
	Control::DeleteInstance();
	DxText::DeleteInstance();
	Dx12Process::DeleteInstance();
}

int loop = 0;

#include <vector>
#include <memory>

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) {

	srand((unsigned)time(NULL));

	if (Createwindow(&hWnd, hInstance, nCmdShow, CURRWIDTH, CURRHEIGHT, L"DirectX_Test") == -1)return FALSE;

	//testDxInput(); return 0;

	//DirectX12ラッパー
	Dx12Process::InstanceCreate();
	dx = Dx12Process::GetInstance();
	con = Control::GetInstance();
	dx->dxrCreateResource();
	dx->setPerspectiveFov(45, 0, 300);
	dx->setNumResourceBarrier(1024);
	dx->Initialize(hWnd, CURRWIDTH, CURRHEIGHT);
	dx->setGlobalAmbientLight(0.01f, 0.01f, 0.01f);
	DxInput* di = DxInput::GetInstance();
	di->create(hWnd);
	di->SetWindowMode(true);
	ui.setNumMeter(8);
	wi.setNumWindow(1);
	di->setCorrectionX(1.015f);
	di->setCorrectionY(1.055f);

	SearchFile* sf = new SearchFile(2);
	char** strE = new char* [2];
	strE[0] = "jpg";
	strE[1] = "png";
	char** strE1 = new char* [1];
	strE1[0] = "tif";
	sf->Search(L"./tex/*", 0, strE, 2);
	//sf->Search(L"../../../53394507/53394507_bldg_6677.fbm/*", 1, strE1, 1);
	//sf->Search(L"../../../Black Dragon NEW/textures/*", 1, strE, 2);
	sf->Search(L"../../../19496_open3dmodel/open3dmodel.com/Models_E0504A019/*", 1, strE, 2);
	//sf->Search(L"../../../Smaug/textures/*", 1, strE, 2);
	//sf->Search(L"../../../sphere-bot-with-hydraulics FBX 7.4 binary/Texture/*", 1, strE, 1);
	//sf->Search(L"../../../106934_open3dmodel.com/Low-Poly Spider/textures/*", 1, strE, 2);
	//sf->Search(L"../../../Alien/textures/*", 1, strE, 2);
	UINT numFile1 = sf->GetFileNum(0);
	UINT numFile2 = sf->GetFileNum(1);
	JPGLoader jpg;
	PNGLoader png;
	TIFLoader tif;
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
			if (byte == nullptr) {
				byte = jpg.loadJPG(str, 0, 0, nullptr);
				w = jpg.getSrcWidth();
				h = jpg.getSrcHeight();
			}
			dx->createTextureArr(numFile1 + numFile2, resCnt++, Dx_Util::GetNameFromPass(str),
				byte, DXGI_FORMAT_R8G8B8A8_UNORM,
				w, w * 4, h);
			ARR_DELETE(byte);
		}
	}

	//文字入力
	DxText::InstanceCreate();
	text = DxText::GetInstance();
	mov = new Movie("tex/torch1.avi");
	blur = new PostEffect();
	mosa = new PostEffect();
	mblur = new PostEffect();

	pd = new PolygonData[numPolygon];
	sk = new SkinMesh();
	sk1 = new SkinMesh();
	md = new MeshData();
	p = new ParticleData();
	bil = new ParticleData();
	wav = new Wave();
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
	arrsk[0].divide = 1;//頂点数 3 → 3 * 6 = 18
	arrsk[1].distance = 50.0f;
	arrsk[1].divide = 1;
	arrsk[2].distance = 36.0f;
	arrsk[2].divide = 1;

	md->setDivideArr(arrsk, 3);
	sk->setDivideArr(arrsk, 3);
	gr->setDivideArr(arr, 3);
	pd[0].setDivideArr(arr, 3);

	p->GetBufferParticle(dx->GetTexNumber("boss_magic.png"), 0.1f, 5.0f);
	bil->GetBufferBill(2);
	bil->SetVertex(0, { 50,0,7 });
	bil->SetVertex(1, { -50,0,18 });
	bil->TextureInit(256, 256);

	wav->SetCommandList(0);
	wav->GetVBarray(1);
	wav->SetVertex(ver24aa, 24, &index36[30], 6);

	gr->GetVBarray(CONTROL_POINT, 1);
	gr->setVertex(ver24aa, 24, &index36[30], 6);

	md->SetCommandList(0);
	md->SetState(true, false, false);
	md->GetBuffer("mesh/tree.obj", 2);
	md->SetVertex();


	sk->SetCommandList(0);
	sk->SetState(false, false);
	//sk->ObjOffset(0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0);
	//sk->GetFbx("mesh/player2_fbx_att.fbx");
	//HRESULT hr = sk->GetFbx("../../../Black Dragon NEW/Dragon_Baked_Actions_fbx_7.4_binary.fbx");
	HRESULT hr = sk->GetFbx("../../../19496_open3dmodel/open3dmodel.com/Models_E0504A019/Crocodile.fbx");
	//HRESULT hr = sk->GetFbx("../../../Smaug/smaug.fbx");
	//HRESULT hr = sk->GetFbx("../../../19496_open3dmodel/open3dmodel.com/Models_E0504A019/wani.fbx");
	//HRESULT hr = sk->GetFbx("../../../sphere-bot-with-hydraulics FBX 7.4 binary/sphere-bot-with-hydraulics.fbx");
	//HRESULT hr = sk->GetFbx("../../../106934_open3dmodel.com/Low-Poly Spider/Spider.fbx");
	//HRESULT hr = sk->GetFbx("../../../Alien/Test_Alien-Animal-Blender_2.81.fbx");
	//HRESULT hr = sk->GetFbx("../../../boss1bone.fbx");

	sk->GetBuffer(1,3200.0f,false);
	//sk->noUseMeshIndex(0);
	sk->SetVertex(true,true);



	sk1->SetCommandList(0);
	sk1->SetState(true, true, 0.0f, 0.0f);
	//sk1->ObjOffset(0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0);
	sk1->GetFbx("mesh/player1_fbx_att.fbx");
	//sk1->GetFbx("../../../53394507/untitled4.fbx");
	//sk1->GetFbx("../../../53394507/untitled.fbx");
	//sk1->GetFbx("../../../53394507/53394507_bldg_6677.fbx");
	sk1->GetBuffer(2,2900.0f,false);
	sk1->SetVertex(true,true);


	pd[0].GetVBarray(CONTROL_POINT, 1);
	pd[1].GetVBarray(SQUARE, 3);
	pd[2].GetVBarray(SQUARE, 2);
	pd[3].GetVBarray(SQUARE, 1);

	VECTOR3 v3[] = { {},{2,0,0},{3,0,0} };
	VECTOR3 v3s[] = { {1,1,1},{1,1,1},{1,1,1} };

	Vertex* sv = (Vertex*)CreateGeometry::createSphere(10, 10, 3, v3, v3s,false);
	unsigned int* svI = CreateGeometry::createSphereIndex(10, 10, 3);
	
	Vertex* v = (Vertex*)CreateGeometry::createCube(2, v3, v3s,false);
	unsigned int* ind = CreateGeometry::createCubeIndex(2);
	pd[0].setVertex(v, 24 * 2, ind, 36 * 2);
	pd[1].setVertex(sv, 11 * 11 * 3, svI, 10 * 10 * 6 * 3);
	pd[2].setVertex(ver24aa, sizeof(ver24aa) / sizeof(Vertex), index36, sizeof(index36) / sizeof(UINT));
	pd[3].setVertex(ver24aa, sizeof(ver24aa) / sizeof(Vertex), index36, sizeof(index36) / sizeof(UINT));

	ARR_DELETE(sv);
	ARR_DELETE(svI);
	ARR_DELETE(v);
	ARR_DELETE(ind);

	soto->GetVBarray(SQUARE, 1);
	soto->setVertex(ver24aaRev, sizeof(ver24aaRev) / sizeof(Vertex), index36Rev, sizeof(index36Rev) / sizeof(UINT));

	dx->Bigin(0);
	blur->ComCreateDepthOfField();
	mosa->ComCreateMosaic();
	mblur->ComCreateBlur();

	p->CreateParticle(dx->GetTexNumber("leaf.png"), true, true);
	bil->setMaterialType(EMISSIVE);
	bil->CreateBillboard(true, true);
	//dx->wireFrameTest(true);
	md->CreateMesh();
	//sk1->setMaterialType(TRANSLUCENCE);
	sk1->CreateFromFBX();
	sk->CreateFromFBX();
	sk->setInternalAnimationIndex(0);

	sk1->setInternalAnimationIndex(0);

	wav->setMaterialType(METALLIC);
	wav->Create(dx->GetTexNumber("wave.jpg"), -1, true, true, 0.031f, 64.0f,true);

	gr->Create(true, dx->GetTexNumber("ground3.jpg"),
		dx->GetTexNumber("ground3Nor.png"),
		dx->GetTexNumber("ground3.jpg"), true, true);

	pd[0].Create(true, dx->GetTexNumber("wall1.jpg"),
		dx->GetTexNumber("wall1Nor.png"),
		dx->GetTexNumber("wall1.jpg"), false, false,false);
	pd[1].setMaterialType(METALLIC);
	pd[1].Create(true, dx->GetTexNumber("ceiling5.jpg"), -1/*dx->GetTexNumber("ceiling5Nor.png")*/, -1, false, false);
	pd[2].setMaterialType(EMISSIVE);
	pd[2].Create(true, dx->GetTexNumber("siro.png"), -1, -1, false, false);
	pd[3].Create(true, dx->GetTexNumber("boss_magic.png"), -1, -1, true, true);

	soto->setMaterialType(DIRECTIONLIGHT_NONREFLECTION);
	soto->Create(true, dx->GetTexNumber("wall1.jpg"),
		dx->GetTexNumber("wall1Nor.png"),
		dx->GetTexNumber("wall1.jpg"), false, false);

	ui.create(0, 200, 50, "mesh1");
	ui.create(1, 200, 50, "cam");
	ui.create(2, 200, 50, "light0");
	ui.create(3, 200, 50, "light1");
	ui.create(4, 200, 50, "light2");
	ui.create(5, 200, 50, "light3");
	ui.create(6, 200, 50, "TMin");
	ui.create(7, 200, 50, "TMax");
	wi.create(0, 15);
	char* str[4];
	char* st0 = "レイトレON";
	char* st1 = "レイトレOFF";

	str[0] = st0;
	str[1] = st1;
	wi.setMenuName(0, 2, str);

	dx->End(0);
	dx->RunGpu();
	dx->WaitFence();

	int numMesh = sk->getNumMesh();
	int numMesh1 = sk1->getNumMesh();
	int numMaterial = 0;
	int numMaterial1 = 0;
	UINT numMT = numPolygon + numMesh + numMesh1 + 5;

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
	pdx[numMesh + numPolygon + numMesh1 + 3] = gr->getParameter();
	pdx[numMesh + numPolygon + numMesh1 + 4] = soto->getParameter();

	dxr = new DXR_Basic();
	dxr->initDXR(numMT, pdx, 10);

	eff[0] = false;
	eff[1] = false;
	eff[2] = false;
	eff[3] = false;
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
		MATRIX camThetaZ;
		VECTOR3 cam1 = { 0, -70, 10 };
		MatrixRotationZ(&camThetaZ, camTheta * 360.0f);
		VectorMatrixMultiply(&cam1, &camThetaZ);
		
		dx->Bigin(0);
		bil->SetTextureMPixel(0, mov->GetFrame(256, 256, 50));
		dx->End(0);

		dxr->allSwapIndex();

		dx->Cameraset({ cam1.x, cam1.y, cam1.z }, { 0, 0, 0 });
		
		th.wait();

		if (!rayF123) {
			dx->RunGpu();
			dx->WaitFence();
		}
		else {
			dx->RunGpuCom();
			dx->RunGpu();
			dx->WaitFenceCom();
			dx->WaitFence();
			UpdateDxrDivideBuffer();

			dx->Bigin(4);
			dxr->copyBackBuffer(4);
			dxr->copyDepthBuffer(4);
			dx->End(4);
			dx->RunGpu();
			dx->WaitFence();
		}

		dx->Bigin(4);
		dx->BiginDraw(4, false);
		p->Draw(4);
		dx->EndDraw(4);
		dx->End(4);
		dx->RunGpu();
		dx->WaitFence();

		dx->Bigin(4);
		dx->BiginDraw(4, false);
		if (loop > 0) {
			if (eff[0])blur->ComputeDepthOfField(4, true, 500, 0.98f, 0.00f);
			else blur->ComputeDepthOfField(4, false, 500, 0.98f, 0.00f);
			if (eff[3])mblur->ComputeBlur(4, true, 400, 400, 0.1f);
			else mblur->ComputeBlur(4, false, 400, 400, 0.1f);
		}
		if (loop > 10000)loop = 3;
		if (eff[1])mosa->ComputeMosaic(4, true, 10);
		else mosa->ComputeMosaic(4, false, 10);
		dx->EndDraw(4);
		dx->End(4);
		dx->RunGpu();
		dx->WaitFence();

		dx->Bigin(4);
		dx->BiginDraw(4, false);
		for (int i = 0; i < 8; i++)
			ui.Draw(i, 4);
		wi.Draw(0, 4);
		text->Draw(4);
		dx->EndDraw(4);
		dx->End(4);
		dx->RunGpu();
		dx->WaitFence();
		dx->DrawScreen();
		loop++;
	}
	th.end();

	dx->WaitFence();
	dx->WaitFenceCom();
	S_DELETE(gr);
	S_DELETE(sf);
	S_DELETE(md);
	S_DELETE(p);
	S_DELETE(bil);
	S_DELETE(mov);
	S_DELETE(wav);
	S_DELETE(blur);
	S_DELETE(mosa);
	S_DELETE(mblur);
	S_DELETE(soto);
	S_DELETE(sk);
	S_DELETE(sk1);
	ARR_DELETE(pd);
	ARR_DELETE(pdx);
	S_DELETE(dxr);
	DxInput::DeleteInstance();
	Control::DeleteInstance();
	DxText::DeleteInstance();
	Dx12Process::DeleteInstance();
	return 0;
}

static bool d = true;

void update() {
	Directionkey key = con->Direction();
	if (key == UP)d = !d;
	if (key == DOWN)eff[0] = !eff[0];//ぼかし
	if (key == LEFT)eff[2] = !eff[2];
	//if (key == ENTER)eff[3] = !eff[3];//Ctrl
	if (key == CANCEL)dlight = !dlight;//Delete
	if (key == RIGHT)eff[3] = !eff[3];

	dx->SetDirectionLight(dlight);
	dx->DirectionLight(0.4f, 0.4f, -1.0f, 0.1f, 0.1f, 0.1f);
	float th = tfloat.Add(0.15f);
	theta = theta += th;
	if (theta > 360)theta = 0;
	MATRIX thetaZ;
	VECTOR3 light1 = { 0, -40, 15 };
	VECTOR3 light2 = { 0,40,15 };
	MatrixRotationZ(&thetaZ, 360 - theta);
	VectorMatrixMultiply(&light1, &thetaZ);
	VectorMatrixMultiply(&light2, &thetaZ);
	int lightCnt = 0;
	static float light[4] = { 0.0f };
	dx->PointLightPosSet(lightCnt++,
		{ light1.x, light1.y, light1.z },
		{ 1, 1, 1, 1 }, true, 1000, { 0.1f,light[0],0.000f });//{ 0.01f,0.001f,0.001f }
	dx->PointLightPosSet(lightCnt++,
		{ light2.x, light2.y, light2.z },
		{ 1, 1, 1, 1 }, true, 1000, { 0.1f,light[1],0.000f });
	dx->PointLightPosSet(lightCnt++,
		{ 14, 0, 5 },
		{ 1, 1, 1, 1 }, true, 1000, { 0.1f,light[2],0.000f });
	dx->PointLightPosSet(lightCnt++,
		{ -14, 0, 5 },
		{ 1, 1, 1, 1 }, true, 1000, { 0.1f,light[3],0.000f });

	float th1 = tfloat.Add(0.05f);

	thetaO = thetaO += th1;
	if (thetaO > 360)thetaO = 0;

	insCnt++;
	if (insCnt > 1100) {
		insCnt = 0;
	}

	pd[0].Instancing({ (float)35, 0, 20 },
		{ 0, 0, thetaO },
		{ 7, 7, 7 }, { 0, 0, 0, 0 });
	pd[0].InstancingUpdate(
		1,
		4.0f);
	float r = (float)(rand() % 11) * 0.1f;
	float g = (float)(rand() % 11) * 0.1f;
	float b1 = (float)(rand() % 11) * 0.1f;
	
	for (int b = 0; b < 3; b++) {
		pd[1].Instancing({ (float)-38, b * 10.0f, 25 },
			{ 0, 0, thetaO },
			{ 7, 7, 7 }, { -r, -g, -b1, 0 });
	}
	pd[1].InstancingUpdate(
		0,
		4.0f);
	pd[1].setRefractiveIndex(0.1f);


	pd[2].Instancing({ light1.x, light1.y, light1.z },
		{ 0, 0, 0 },
		{ 1, 1, 1 }, { 0, 0, 0, 0 });

	pd[2].Instancing({ light2.x, light2.y, light2.z },
		{ 0, 0, 0 },
		{ 1, 1, 1 }, { 0, 0, 0, 0 });
	pd[2].InstancingUpdate(
		0,
		4.0f);

	pd[3].Instancing({ 0, 0, 15 },
		{ 0, 0, thetaO },
		{ 4, 4, 4 }, { 0, 0, 0, 0 });
	pd[3].InstancingUpdate(
		0,
		4.0f);

	float m = tfloat.Add(1.0f);

	
	/*sk->Update(0, m,
		{ 10, 0, 0 },
		{ 0, 0, 0, 0 },
		{ 0, 0, 0 },
		{ 0.005f,0.005f,0.005f });*/

	sk->Update(0, m,
		{ 2, -5, 0 },
		{ 0, 0, 0, 0 },
		{ 90, 0, 0 },
		{ 0.2f,0.2f,0.2f });

	/*sk->Update(0, m,
		{ 5, 0, 0 },
		{ 0, 0, 0, 0 },
		{ 0, 0, 0 },
		{ 1.6f,1.6f,1.6f });*/
	sk->setAllRefractiveIndex(0.1f);
	//}
	//else sk->DrawOff();

	static float Refractive = 0.0f;
	for (int i = 0; i < 2; i++) {
		sk1->Instancing({ (float)-20+i*15.0f, 0, 0 },
			{ 0, 0, 0, -0.00f },
			{ -90, 0, 0 },
			{ 1.6f,1.6f,1.6f });
	}
	sk1->InstancingUpdate(0, m);
	/*sk1->Update(0, m,
		{ -20, 0, 0 },
		{ 0, 0, 0, -0.00f },
		{-90, 0, 0 },
		{ 1.6f,1.6f,1.6f });*/
	sk1->setAllRefractiveIndex(Refractive);

	md->Instancing({ 0, 0, -10 },
		{ 0, 0, 0 },
		{ 1,1,1 }, { 0, 0, 0, 0 });
	md->Instancing({ 0, 0, 30 },
		{ 0, 0, 0 },
		{ 1,1,1 }, { 0, 0, 0, 0 });
	md->InstancingUpdate(
		0, 4.0);

	float m2 = tfloat.Add(0.003f);
	if (d) {
		wav->Instancing(m2, { 0, 0, -20 },
			{ 0,0,0 },
			{ 60, 60, 15 }, { 0, 0, 0, -0.1f });
		wav->InstancingUpdate(
			0.0000f, 4.0f);
	}
	else wav->DrawOff();

	gr->Instancing({ 0, 0, -28 },
		{ 0, 0, 0 },
		{ 60, 60, 15 }, { 0, 0, 0, 0 });

	gr->InstancingUpdate(
		0.01f,
		1.0f);

	soto->Instancing({ 0, 0, 0 },
		{ 0, 0, 0 },
		{ 60, 60, 60 }, { 0, 0, 0, 0 });
	soto->InstancingUpdate(
		0,
		4.0f);

	float sp1 = tfloat.Add(0.03f);
	parCnt += sp1;
	if (parCnt > 3) {
		parCnt = 0; parSwich = true;
	}
	float sp = tfloat.Add(0.03f);
	if (1) {
		p->Update({ 0,0,5 }, { 0,0,0 }, 0, 0.1f, parSwich, sp);
		parSwich = false;
		//bil->Update(10.0f, { 0,0,0,-0.3f });
		bil->Update({5,0,0}, { 0,0,0,-0.3f }, 50, 10.0f, false, 0);
	}
	else {
		p->DrawOff();
		bil->DrawOff();
	}

	static bool uiF = false;
	if (!uiF) {
		ui.updatePos(0, 1, 1, 0, 0);
		ui.updatePos(1, 822, 716, 0, 0);
		ui.updatePos(2, 1, 100, 0, 0);
		ui.updatePos(3, 1, 200, 0, 0);
		ui.updatePos(4, 1, 300, 0, 0);
		ui.updatePos(5, 1, 400, 0, 0);
		ui.updatePos(6, 1, 500, 0, 0);
		ui.updatePos(7, 1, 600, 0, 0);
		uiF = true;
	}
	else
	{
		Refractive = ui.updatePosMouse(0, 0.0f);
		camTheta = ui.updatePosMouse(1, 0.0f);
		light[0] = 1.0f - ui.updatePosMouse(2, 0.0f);
		light[1] = 1.0f - ui.updatePosMouse(3, 0.0f);
		light[2] = 1.0f - ui.updatePosMouse(4, 0.0f);
		light[3] = 1.0f - ui.updatePosMouse(5, 0.0f);
		float tMin = 0.001f + 200.0f * ui.updatePosMouse(6, 0.0f);
		float tMax = 300.0f - 300.0f * ui.updatePosMouse(7, 0.0f);
		dxr->setTMin_TMax(tMin, tMax);
	}
	int rF = wi.updatePos(0, 200, 100);
	if (rF == 0)rayF123 = true;
	if (rF == 1)rayF123 = false;

	if (!eff[1])
		text->UpDateText(L"モザイクオフ", 185.0f, 60.0f, 30.0f, { 1.0f, 1.0f, 1.0f, 1.0f });
	else
		text->UpDateText(L"モザイクオン", 185.0f, 60.0f, 30.0f, { 1.0f, 0.0f, 0.0f, 1.0f });
	text->UpDate();

	if (Dx_Util::getErrorState()) {
		int g = 0;
	}
}

void draw() {
	int com = 1;
	if (rayF123 == false) {
		dx->Bigin(com);
		dx->BiginDraw(com);
		soto->Draw(com);
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
	}
	else {
		dx->Bigin(com);
		sk->StreamOutput(com);//update
		sk1->StreamOutput(com);//update
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
	}
}

void UpdateDxrDivideBuffer() {
	sk->UpdateDxrDivideBuffer();
	sk1->UpdateDxrDivideBuffer();
	pd[0].UpdateDxrDivideBuffer();
	wav->UpdateDxrDivideBuffer();
	gr->UpdateDxrDivideBuffer();
}

void AS() {
	int com = 2;
	if (rayF123) {
		dx->Bigin(com);
		dxr->update_g(com, 6);
		dx->End(com);
	}
}

void raytrace() {
	int com = 3;
	if (rayF123) {
		dx->BiginCom(com);
		dxr->raytrace_c(com);
		dx->EndCom(com);
	}
}
