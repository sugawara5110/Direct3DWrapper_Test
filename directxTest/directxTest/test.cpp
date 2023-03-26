//////////////////////////////////////DirectXテスト/////////////////////////////////////////////////////////////

#define _CRT_SECURE_NO_WARNINGS
#include"../../../T_float/T_float.h"
#include"../../../Common/Direct3DWrapper/Dx12Process.h"
#include"../../../Common/Direct3DWrapperOption/DxText.h"
#include"../../../Common/Direct3DWrapperOption/Dx_ParticleData.h"
#include"../../../Common/Direct3DWrapperOption/Dx_PostEffect.h"
#include"../../../Common/Direct3DWrapperOption/Dx_Wave.h"
#include"../../../Common/Direct3DWrapperOption/Dx_Bloom.h"
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
#include"../../../Common/DirectStorageWrapper/DStorage.h"
#include "SkinObj/SkinObj.h"
#include "testCode.h"
#define CURRWIDTH 1024
#define CURRHEIGHT 768

using namespace CoordTf;

static Vertex ver4[] =
{
	{ {-1.0f, -1.0f, 1.0f}, {0.0f, 0.0f, 1.0f} ,{0.0f,0.0f}},
	{ {1.0f, -1.0f, 1.0f}, {0.0f, 0.0f, 1.0f} ,{1.0f,0.0f}},
	{ {1.0f, 1.0f, 1.0f}, {0.0f, 0.0f, 1.0f} ,{1.0f,1.0f}},
	{ {-1.0f, 1.0f, 1.0f}, {0.0f, 0.0f, 1.0f} ,{0.0f,1.0f}},
};

static UINT index6[] =
{
	0,1,2,
	0,2,3
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
static bool rayF123 = false;
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
DxText* text;
DxrRenderer* dxr;
PolygonData* pd;
PolygonData* pdbl;
SkinMesh* sk;
SkinObj* sk1;
MeshData* md;
Wave* wav;
ParticleData* p;
ParticleData* bil;
PolygonData* gr;
PolygonData* soto;
Movie* mov;
PostEffect* blur, * mosa, * mblur, *gau;
Control* con;
UserInterfaceMeter* ui;//new生成に変更※解放順の関係
UserInterfaceWindow* wi;//new生成に変更※解放順の関係
Dx_Bloom* bl;

static float BloomStrength = 0.0f;
static float ThresholdLuminance = 0.0f;
static float BloomStrength2 = 0.0f;
static float ThresholdLuminance2 = 0.0f;
static float BloomStrength3 = 0.0f;
static float ThresholdLuminance3 = 0.0f;

int loop = 0;

#include <vector>
#include <memory>

void createTexture(Dx_TextureHolder* dx) {
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
	S_DELETE(sf);
}

void createTexture2(Dx_TextureHolder* dx) {
	SearchFile* sf = new SearchFile(2);
	char** strE = new char* [2];
	strE[0] = "jpg";
	strE[1] = "png";
	char** strE1 = new char* [1];
	strE1[0] = "tif";
	sf->Search(L"./tex/*", 0, strE, 2);
	//sf->Search(L"../../../19496_open3dmodel/open3dmodel.com/Models_E0504A019/*", 1, strE, 2);
	sf->Search(L"../../../Black Dragon NEW/textures/*", 1, strE, 2);
	UINT numFile1 = sf->GetFileNum(0);
	UINT numFile2 = sf->GetFileNum(1);
	InputParameter* ip = new InputParameter[numFile1 + numFile2];
	
	ARR_DELETE(strE);
	int cnt = 0;
	for (int k = 0; k < 2; k++) {
		for (int i = 0; i < sf->GetFileNum(k); i++) {
			char* str = sf->GetFileName(k, i);
			ip[cnt].width = 512;
			ip[cnt].height = 512;
			ip[cnt].format = DXGI_FORMAT_R8G8B8A8_UNORM;
			ip[cnt++].setFileName(str);
		}
	}
	ID3D12Device* device = Dx_Device::GetInstance()->getDevice();
	std::unique_ptr<OutputResource[]> R = DStorage::Load(device, ip, numFile1 + numFile2);
	DStorage::Delete();

	for (int i = 0; i < numFile1 + numFile2; i++) {
		dx->createTextureArr(numFile1 + numFile2, i, Dx_Util::GetNameFromPass(ip[i].getFileName()),
			R[i].Subresource, ip[i].format,
			ip[i].width, ip[i].width * 4, ip[i].height, R[i].Texture);
	}

	ARR_DELETE(ip);
	S_DELETE(sf);
}

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) {

	srand((unsigned)time(NULL));

	if (Createwindow(&hWnd, hInstance, nCmdShow, CURRWIDTH, CURRHEIGHT, L"DirectX_Test") == -1)return FALSE;

	//DirectX12ラッパー
	Dx_Device::InstanceCreate();
	Dx_Device::GetInstance()->createDevice();
	Dx_Device::GetInstance()->reportLiveDeviceObjectsOn();
	Dx_CommandManager::InstanceCreate();
	Dx_SwapChain::InstanceCreate();

	Dx_TextureHolder::InstanceCreate();
	Dx_TextureHolder* dx = Dx_TextureHolder::GetInstance();
	con = Control::GetInstance();
	Dx_Device* dev = Dx_Device::GetInstance();
	dev->dxrCreateResource();
	Dx_SwapChain* sw = Dx_SwapChain::GetInstance();

	Dx_CommandManager::setNumResourceBarrier(1024);

	sw->Initialize(hWnd, CURRWIDTH, CURRHEIGHT);

	sw->setPerspectiveFov(55, 1, 10000);
	Dx_Light::Initialize();
	Dx_ShaderHolder::CreateShaderByteCode();

	//dx->wireFrameTest(true);
	//Dx_ShaderHolder::NorTestOn();
	Dx_Light::setGlobalAmbientLight(0.0000f, 0.0000f, 0.0000f);
	DxInput* di = DxInput::GetInstance();
	di->create(hWnd);
	di->SetWindowMode(true);
	ui = new UserInterfaceMeter();
	wi = new UserInterfaceWindow();
	ui->setNumMeter(14);
	wi->setNumWindow(1);
	di->setCorrectionX(1.015f);
	di->setCorrectionY(1.055f);

	createTexture2(dx);

	//文字入力
	DxText::InstanceCreate();
	text = DxText::GetInstance();
	mov = new Movie("tex/torch1.avi");
	blur = new PostEffect();
	mosa = new PostEffect();
	mblur = new PostEffect();
	gau = new PostEffect();

	pd = new PolygonData[numPolygon];
	pdbl = new PolygonData[2];

	sk = new SkinMesh();
	sk1 = new SkinObj();
	md = new MeshData();
	p = new ParticleData();
	bil = new ParticleData();
	wav = new Wave();
	soto = new PolygonData();
	gr = new PolygonData();

	DivideArr arr[3];
	arr[0].distance = 90.0f;
	arr[0].divide = 16;//頂点数 3 → 3 * 6 = 18
	arr[1].distance = 50.0f;
	arr[1].divide = 32;//頂点数 3 → 3 * 3456 = 10368
	arr[2].distance = 36.0f;
	arr[2].divide = 64;//頂点数 3 → 3 * 13824 = 41472

	DivideArr arrsk[3];
	arrsk[0].distance = 90.0f;
	arrsk[0].divide = 1;//頂点数 3 → 3 * 6 = 18
	arrsk[1].distance = 50.0f;
	arrsk[1].divide = 1;
	arrsk[2].distance = 36.0f;
	arrsk[2].divide = 1;

	DivideArr arrWv[3];
	arrWv[0].distance = 1000.0f;
	arrWv[0].divide = 64;//頂点数 3 → 3 * 6 = 18
	arrWv[1].distance = 50.0f;
	arrWv[1].divide = 64;
	arrWv[2].distance = 36.0f;
	arrWv[2].divide = 64;

	wav->setDivideArr(arrWv, 3);
	md->setDivideArr(arrsk, 3);
	sk->setDivideArr(arrsk, 3);
	gr->setDivideArr(arr, 3);
	pd[0].setDivideArr(arr, 3);
	pd[3].setDivideArr(arr, 3);

	p->GetBufferParticle(dx->GetTexNumber("boss_magic.png"), 0.1f, 5.0f);
	bil->GetBufferBill(2);
	bil->SetVertex(0, { 50,0,7 });
	bil->SetVertex(1, { -50,0,18 });
	bil->TextureInit(256, 256);

	md->SetState(true, false, false);
	md->GetBuffer("mesh/tree.obj", 2);
	md->SetVertex();

	sk->SetState(false, false);
	//sk->ObjOffset(0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0);
	//sk->GetFbx("mesh/player2_fbx_att.fbx");
	HRESULT hr = sk->GetFbx("../../../Black Dragon NEW/Dragon_Baked_Actions_fbx_7.4_binary.fbx");
	//HRESULT hr = sk->GetFbx("../../../19496_open3dmodel/open3dmodel.com/Models_E0504A019/Crocodile.fbx");
	//HRESULT hr = sk->GetFbx("../../../Smaug/smaug.fbx");
	//HRESULT hr = sk->GetFbx("../../../19496_open3dmodel/open3dmodel.com/Models_E0504A019/wani.fbx");
	//HRESULT hr = sk->GetFbx("../../../sphere-bot-with-hydraulics FBX 7.4 binary/sphere-bot-with-hydraulics.fbx");
	//HRESULT hr = sk->GetFbx("../../../106934_open3dmodel.com/Low-Poly Spider/Spider.fbx");
	//HRESULT hr = sk->GetFbx("../../../Alien/Test_Alien-Animal-Blender_2.81.fbx");
	//HRESULT hr = sk->GetFbx("../../../boss1bone.fbx");


	float end_frame[3] = {
		sk->getMaxEndframe(0,0),
		sk->getMaxEndframe(0,1),
		sk->getMaxEndframe(0,2)
	};

	sk->GetBuffer(1, 3,
		end_frame,
		false);
	//sk->noUseMeshIndex(0);
	sk->SetVertex(true, true);

	pd[0].GetVBarray(SQUARE, 1);
	pd[1].GetVBarray(SQUARE, 3);
	pdbl[0].GetVBarray(SQUARE, 1);
	pdbl[1].GetVBarray(SQUARE, 1);
	pd[2].GetVBarray(SQUARE, 1);
	pd[3].GetVBarray(CONTROL_POINT, 1);

	VECTOR3 v3[] = { {} };
	VECTOR3 v3s[] = { {1,1,1} };

	Vertex* sv = (Vertex*)CreateGeometry::createSphere(10, 10, 1, v3, v3s, false);
	unsigned int* svI = CreateGeometry::createSphereIndex(10, 10, 1);

	Vertex* v = (Vertex*)CreateGeometry::createCube(1, v3, v3s, false);
	Vertex* vRev = (Vertex*)CreateGeometry::createCube(1, v3, v3s, true);

	unsigned int* ind = CreateGeometry::createCubeIndex(1);
	pd[0].setVertex(v, 24, ind, 36);
	pd[1].setVertex(sv, 11 * 11, svI, 10 * 10 * 6);
	pdbl[0].setVertex(v, 24, ind, 36);
	pdbl[1].setVertex(v, 24, ind, 36);
	pd[2].setVertex(v, 24, ind, 36);
	pd[3].setVertex(ver4, 4, index6, 6);

	wav->GetVBarray(1);
	//wav->SetVertex(v, 24, &ind[30], 6);
	wav->SetVertex(ver4, 4, index6, 6);

	gr->GetVBarray(CONTROL_POINT, 1);
	gr->setVertex(v, 24, &ind[30], 6);

	soto->GetVBarray(SQUARE, 1);
	soto->setVertex(vRev, 24, ind, 36);

	ARR_DELETE(sv);
	ARR_DELETE(svI);
	ARR_DELETE(v);
	ARR_DELETE(vRev);
	ARR_DELETE(ind);

	Dx_CommandManager* cMa = Dx_CommandManager::GetInstance();
	Dx_CommandListObj* cObj = cMa->getGraphicsComListObj(0);

	cObj->Bigin();

	blur->ComCreateDepthOfField(0);
	mosa->ComCreateMosaic(0);
	mblur->ComCreateBlur(0);
	UINT gaSize[5] = {
		//512,256,128,64,32,16,8
		256,128,64,32,16
	};

	p->CreateParticle(0, dx->GetTexNumber("leaf.png"), true, true);
	bil->setMaterialType(EMISSIVE);
	bil->CreateBillboard(0, true, true);
	md->CreateMesh(0);
	//sk1->setMaterialType(TRANSLUCENCE);
	//sk1->setMaterialType(EMISSIVE,0,3);
	//sk1->ObjCentering(true, 0);
	sk1->create();
	sk->CreateFromFBX(0);

	wav->SetCol(0.5f, 0.5f, 0.5f, 1, 1, 1);
	wav->setMaterialType((MaterialType)(TRANSLUCENCE | METALLIC));
	wav->Create(0, -1/*dx->GetTexNumber("maru.png")*//*dx->GetTexNumber("wave.jpg")*/, -1, true, true, 0.05f, 64.0f, true);

	//gr->setMaterialType(METALLIC);
	gr->Create(0, true, dx->GetTexNumber("ground3.jpg"),
		dx->GetTexNumber("ground3Nor.png"),
		dx->GetTexNumber("ground3.jpg"), true, true, true);
	//gr->getParameter()->updateF = true;

	
	pd[0].Create(0,true, dx->GetTexNumber("wall1.jpg"),
		dx->GetTexNumber("wall1Nor.png"),
		dx->GetTexNumber("wall1.jpg"), false, false, false);
		
	pd[1].setMaterialType(METALLIC);
	pd[1].Create(0,true, dx->GetTexNumber("siro.png"), -1/*dx->GetTexNumber("ceiling5Nor.png")*/, -1, false, true);
	pdbl[0].setMaterialType(EMISSIVE);
	pdbl[0].Create(0,true, dx->GetTexNumber("siro.png"), -1, -1, false, false);
	pdbl[1].setMaterialType(EMISSIVE);
	pdbl[1].Create(0,true, dx->GetTexNumber("siro.png"), -1, -1, false, false);
	pd[2].Create(0,true, dx->GetTexNumber("boss_magic.png"), -1, -1, true, true);
	pd[3].setMaterialType(TRANSLUCENCE);
	pd[3].Create(0,true, dx->GetTexNumber("siro.png"),dx->GetTexNumber("wall1Nor.png"),-1, false, false, false);

	soto->setMaterialType((MaterialType)(DIRECTIONLIGHT | NONREFLECTION));
	soto->Create(0,true, dx->GetTexNumber("wall1.jpg"),
		dx->GetTexNumber("wall1Nor.png"),
		dx->GetTexNumber("wall1.jpg"), false, false);
	
	ui->create(0, 200, 50, "smoothRange");
	ui->create(1, 200, 50, "cam");
	ui->create(2, 200, 50, "light0");
	ui->create(3, 200, 50, "light1");
	ui->create(4, 200, 50, "light2");
	ui->create(5, 200, 50, "light3");
	ui->create(6, 200, 50, "TMin");
	ui->create(7, 200, 50, "TMax");
	ui->create(8, 200, 50, "ブルーム強さ");
	ui->create(9, 200, 50, "輝度閾値");
	ui->create(10, 200, 50, "ブルーム強さ2");
	ui->create(11, 200, 50, "輝度閾値2");
	ui->create(12, 200, 50, "ブルーム強さ3");
	ui->create(13, 200, 50, "輝度閾値3");
	wi->create(0, 15);
	char* str[4];
	char* st0 = "レイトレON";
	char* st1 = "レイトレOFF";

	str[0] = st0;
	str[1] = st1;
	wi->setMenuName(0, 2, str);

	cObj->End();
	cMa->RunGpu();
	cMa->WaitFence();

	int numMesh = sk->getNumMesh();
	int numMesh1 = sk1->getNumParameterDXR();
	
	std::vector<ParameterDXR*> pdx;

	for (int i = 0; i < numPolygon; i++)
		pdx.push_back(pd[i].getParameter());
	for (int i = 0; i < numMesh; i++) {
		pdx.push_back(sk->getParameter(i));
	}
	for (int i = 0; i < numMesh1; i++) {
		pdx.push_back(sk1->getParameterDXR(i));
	}
	pdx.push_back(md->getParameter());
	pdx.push_back(wav->getParameter());
	pdx.push_back(bil->getParameter());
	pdx.push_back(gr->getParameter());
	pdx.push_back(soto->getParameter());
	pdx.push_back(pdbl[0].getParameter());
	pdx.push_back(pdbl[1].getParameter());
	dxr = new DxrRenderer();
	dxr->initDXR(pdx, 10);
	bl = new Dx_Bloom();
	std::vector<std::vector<uint32_t>> gausu = {
		{128, 32},
		{128, 32,8},
		{128,32,8}
	};
	std::vector<float> sigma = { 10,15,12 };
	std::vector<Dx_Bloom::GaussianType> type = { Dx_Bloom::GaussianType::Type1D, Dx_Bloom::GaussianType::Type1D, Dx_Bloom::GaussianType::Type1D };

	bl->Create(0,3,dxr->getInstanceIdMap(),&sigma,&gausu,&type);

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
		VECTOR3 cam1 = { 0, -90, 10 };
		MatrixRotationZ(&camThetaZ, camTheta * 360.0f);
		VectorMatrixMultiply(&cam1, &camThetaZ);

		cObj->Bigin();
		bil->SetTextureMPixel(0, mov->GetFrame(256, 256, 50));
		cObj->End();

		dxr->allSwapIndex();

		sw->Cameraset({ cam1.x, cam1.y, cam1.z }, { 0, 0, 0 });
		//グラフィックスドライバ更新した後当たりからマルチスレッドでフリーズする現象有り？ → 大丈夫になった・・
		//update();
		//draw();
		//AS();
		//raytrace();
		th.wait();

		//ラスタ
		cMa->RunGpu();
		cMa->WaitFence();

		Dx_CommandListObj* cObj4 = cMa->getGraphicsComListObj(4);
		if (rayF123) {
			//レイトレ
			cMa->RunGpuCom();
			cMa->RunGpu();
			cMa->WaitFenceCom();
			cMa->WaitFence();
			UpdateDxrDivideBuffer();

			cObj4->Bigin();
			dxr->copyBackBuffer(4);
			dxr->copyDepthBuffer(4);
			cObj4->End();
			cMa->RunGpu();
			cMa->WaitFence();
		}

		cObj4->Bigin();
		sw->BiginDraw(4, false);
		//p->Draw(4);
		sw->EndDraw(4);
		cObj4->End();
		cMa->RunGpu();
		cMa->WaitFence();

		cObj4->Bigin();
		sw->BiginDraw(4, false);

		if (loop > 0) {
			if (eff[0])blur->ComputeDepthOfField(4, true, 500, 0.98f, 0.00f);
			else blur->ComputeDepthOfField(4, false, 500, 0.98f, 0.00f);
			if (eff[3])mblur->ComputeBlur(4, true, 400, 400, 0.1f);
			else mblur->ComputeBlur(4, false, 400, 400, 0.1f);
		}
		if (loop > 10000)loop = 3;
		//if (eff[1])mosa->ComputeMosaic(4, true, 10);
		//else mosa->ComputeMosaic(4, false, 10);



		sw->EndDraw(4);
		cObj4->End();
		cMa->RunGpu();
		cMa->WaitFence();

		if (rayF123) {
			Dx_Bloom::InstanceParam pa1 = {};
			pa1.bloomStrength = BloomStrength;
			pa1.EmissiveInstanceId = pdx.size() - 5 + 3;
			pa1.thresholdLuminance = ThresholdLuminance;
			Dx_Bloom::InstanceParam pa2 = {};
			pa2.bloomStrength = BloomStrength2;
			pa2.EmissiveInstanceId = pdx.size() - 2 + 3;
			pa2.thresholdLuminance = ThresholdLuminance2;
			Dx_Bloom::InstanceParam pa3 = {};
			pa3.bloomStrength = BloomStrength3;
			pa3.EmissiveInstanceId = pdx.size() - 1 + 3;
			pa3.thresholdLuminance = ThresholdLuminance3;

			std::vector<Dx_Bloom::InstanceParam>pa = { pa1,pa2,pa3};

			bl->Compute(4, pa, sw->GetRtBuffer());
		}

		cObj4->Bigin();
		sw->BiginDraw(4, false);
		
		for (int i = 0; i < 14; i++)
			ui->Draw(i, 4);
		wi->Draw(0, 4);
		text->Draw(4);
		sw->EndDraw(4);
		cObj4->End();
		cMa->RunGpu();
		cMa->WaitFence();
		sw->DrawScreen();
		loop++;
	}
	th.end();

	cMa->WaitFence();
	cMa->WaitFenceCom();
	S_DELETE(wi);
	S_DELETE(ui);
	S_DELETE(bl);
	S_DELETE(gr);
	S_DELETE(md);
	S_DELETE(p);
	S_DELETE(bil);
	S_DELETE(mov);
	S_DELETE(wav);
	S_DELETE(blur);
	S_DELETE(mosa);
	S_DELETE(mblur);
	S_DELETE(gau);
	S_DELETE(soto);
	S_DELETE(sk);
	S_DELETE(sk1);
	ARR_DELETE(pd);
	ARR_DELETE(pdbl);
	S_DELETE(dxr);
	DxInput::DeleteInstance();
	Control::DeleteInstance();
	DxText::DeleteInstance();
	Dx_SwapChain::DeleteInstance();
	Dx_TextureHolder::DeleteInstance();
	Dx_CommandManager::DeleteInstance();
	Dx_Device::DeleteInstance();
	return 0;
}

static bool d = true;

void update() {
	
	Directionkey key = con->Direction();
	if (key == UP)d = !d;
	if (key == DOWN)eff[0] = !eff[0];//被写界深度
	if (key == LEFT)eff[1] = !eff[1];//bloom
	//if (key == ENTER)eff[1] = !eff[1];//Ctrl
	if (key == CANCEL)dlight = !dlight;//Delete
	if (key == RIGHT)eff[3] = !eff[3];//ブラー

	Dx_Light::SetDirectionLight(dlight);
	Dx_Light::DirectionLight(0.4f, 0.4f, -1.0f, 0.1f, 0.1f, 0.1f);
	float th = tfloat.Add(0.05f);
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
	Dx_Light::PointLightPosSet(lightCnt++,
		{ light1.x, light1.y, light1.z },
		{ 1, 1, 1, 1 }, true, 1000, { 0.1f,light[0],0.000f });//{ 0.01f,0.001f,0.001f }
	Dx_Light::PointLightPosSet(lightCnt++,
		{ light2.x, light2.y, light2.z },
		{ 1, 1, 1, 1 }, true, 1000, { 0.1f,light[1],0.000f });
	Dx_Light::PointLightPosSet(lightCnt++,
		{ 14, 0, 5 },
		{ 1, 1, 1, 1 }, true, 1000, { 0.1f,light[2],0.000f });
	Dx_Light::PointLightPosSet(lightCnt++,
		{ -14, 0, 5 },
		{ 1, 1, 1, 1 }, true, 1000, { 0.1f,light[3],0.000f });
		
	float th1 = tfloat.Add(0.005f);

	thetaO = thetaO += th1;
	if (thetaO > 360)thetaO = 0;

	insCnt++;
	if (insCnt > 1100) {
		insCnt = 0;
	}
	
	pd[0].Instancing({ (float)0, 0, 10 },
		{ 0, 0, 0 },
		{ 7, 7, 7 }, { 0, 0, 0, 0 });
	pd[0].InstancingUpdate(
		0.2f,
		0.2f,
		4.0f);

	pd[1].Instancing({ (float)0, -3.0f, 15 },
		{ 0, 0, thetaO },
		{ 7, 7, 7 }, { 0, 0, 0, 0 });
	pd[1].InstancingUpdate(
		0,
		4.0f);
	pd[1].setRefractiveIndex(0.1f);


	pdbl[0].Instancing({ light1.x, light1.y, light1.z },
		{ 0, 0, 0 },
		{ 1, 1, 1 }, { 0, 0, 0, 0 });
	pdbl[0].InstancingUpdate(
		0,
		4.0f);
	pdbl[1].Instancing({ light2.x, light2.y, light2.z },
		{ 0, 0, 0 },
		{ 1, 1, 1 }, { 0, 0, 0, 0 });
	pdbl[1].InstancingUpdate(
		0,
		4.0f);
	pdbl[0].setPointLight(0, true, 1000, { 0.5f,light[0],0.000f });
	pdbl[1].setPointLight(0, true, 1000, { 0.5f,light[1],0.000f });

	pd[2].Instancing({ 0, 0, 15 },
		{ 0, 0, thetaO },
		{ 4, 4, 4 }, { 0, 0, 0, 0 });
	pd[2].InstancingUpdate(
		0,
		4.0f);

	pd[3].Instancing({ 0, -20, 8 },
		{ 90, 0, 0 },
		{ 10, 10, 10 }, { 0, 0, 0, -0.4f });
	pd[3].InstancingUpdate(
		0,
		4.0f);
	pd[3].setRefractiveIndex(0.1f);

	float m = tfloat.Add(0.1f);
	sk->setDirectTime(300.0f);
	/*
	sk->Update(0, m,
		{ 2, -5, 0 },
		{ 0, 0, 0, 0 },
		{ 90, 0, 0 },
		{ 0.2f,0.2f,0.2f });//19496_open3dmodel
		*/
	sk->Update(0, m,
		{ 15, -5, 0 },
		{ 0, 0, 0, 0 },
		{ 90, 0, 0 },
		{ 0.005f,0.005f,0.005f },2);//Dragon

	sk->setAllRefractiveIndex(0.1f);
	
	static float Refractive = 0.3f;
	sk1->update();

	md->Instancing({ 10, 0, 10 },
		{ 0, 0, 0 },
		{ 1,1,1 }, { 0, 0, 0, 0 });
	/*md->Instancing({0, 0, 30},
		{ 0, 0, 0 },
		{ 1,1,1 }, { 0, 0, 0, 0 });*/
	md->InstancingUpdate(
		0, 4.0);

	static float smoothRange = 0.0f;
	float m2 = tfloat.Add(0.03f);
	m2 = 1.1f;//波紋
	
	if (d) {
		wav->Instancing({ 0, 0, -20 },
			{ 0,0,thetaO },
			{ 60, 60, 15 }, { 0, 0, 0, -0.2f });
		wav->InstancingUpdate(1, m2,
			0.0f, smoothRange, 32, 32, 0.7f);
	}
	else wav->DrawOff();
	wav->setRefractiveIndex(0.1f);

	gr->Instancing({ 0, 0, -28 },
		{ 0, 0, 0 },
		{ 60, 60, 15 }, { 0, 0, 0, 0 });

	static float px = 0.0f;
	static float py = 0.0f;
	static float u_num = 0.0f;
	static float v_num = 0.0f;

	gr->InstancingUpdate(
		0.0f, 0.1f, 1.0f, 4.0f);

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
		
		bil->Update({ 5,0,0 }, { 0,0,0,-0.3f }, 50, 10.0f, false, 0);
		bil->setPointLight(0, true, 1000, { 0.5f,light[2],0.000f });
		bil->setPointLight(1, true, 1000, { 0.5f,light[3],0.000f });
	}
	else {
		p->DrawOff();
		bil->DrawOff();
	}

	
	static bool uiF = false;
	if (!uiF) {
		
		ui->updatePos(0, 1, 1, 0, 0);
		ui->updatePos(1, 822, 716, 0, 0);
		ui->updatePos(2, 1, 100, 0, 0);
		ui->updatePos(3, 1, 200, 0, 0);
		ui->updatePos(4, 1, 300, 0, 0);
		ui->updatePos(5, 1, 400, 0, 0);
		ui->updatePos(6, 1, 500, 0, 0);
		ui->updatePos(7, 1, 600, 0, 0);
		ui->updatePos(8, 822, 1, 0, 0);
		ui->updatePos(9, 822, 100, 0, 0);
		ui->updatePos(10, 822, 200, 0, 0);
		ui->updatePos(11, 822, 300, 0, 0);
		ui->updatePos(12, 822, 400, 0, 0);
		ui->updatePos(13, 822, 500, 0, 0);
		
		uiF = true;
	}
	else
	{
		smoothRange = ui->updatePosMouse(0, 0.0f);
		camTheta = ui->updatePosMouse(1, 0.0f);
		light[0] = 1.0f - ui->updatePosMouse(2, 0.0f);
		light[1] = 1.0f - ui->updatePosMouse(3, 0.0f);
		light[2] = 1.0f - ui->updatePosMouse(4, 0.0f);
		light[3] = 1.0f - ui->updatePosMouse(5, 0.0f);
		float tMin = 0.001f + 200.0f * ui->updatePosMouse(6, 0.0f);
		float tMax = 300.0f - 300.0f * ui->updatePosMouse(7, 0.0f);
		BloomStrength = ui->updatePosMouse(8, 0.0f) * 50.0f;
		ThresholdLuminance = ui->updatePosMouse(9, 0.0f);
		BloomStrength2 = ui->updatePosMouse(10, 0.0f) * 50.0f;
		ThresholdLuminance2 = ui->updatePosMouse(11, 0.0f);
		BloomStrength3 = ui->updatePosMouse(12, 0.0f) * 50.0f;
		ThresholdLuminance3 = ui->updatePosMouse(13, 0.0f);
		
		dxr->setTMin_TMax(tMin, tMax);
	}
	int rF = wi->updatePos(0, 200, 100);
	if (rF == 0)rayF123 = true;
	if (rF == 1)rayF123 = false;

	if (!eff[1])
		text->UpDateText(L"ブルームオフ", 185.0f, 60.0f, 30.0f, { 1.0f, 1.0f, 1.0f, 1.0f });
	else
		text->UpDateText(L"ブルームオン", 185.0f, 60.0f, 30.0f, { 1.0f, 0.0f, 0.0f, 1.0f });
	text->UpDate();
	
	if (Dx_Util::getErrorState()) {
		int g = 0;
	}
}

void draw() {
	int com = 1;
	
	Dx_CommandListObj* d = Dx_CommandManager::GetInstance()->getGraphicsComListObj(com);
	Dx_SwapChain* sw = Dx_SwapChain::GetInstance();

	d->Bigin();
	if (!rayF123) {
		sw->BiginDraw(com);
		sk1->Draw(com);
		pdbl[0].Draw(com);
		pdbl[1].Draw(com);
		soto->Draw(com);
		pd[1].Draw(com);
		pd[2].Draw(com);
		md->Draw(com);
		gr->Draw(com);
		wav->Draw(com);
		sk->Draw(com);
		pd[0].Draw(com);
		pd[3].Draw(com);
		bil->DrawBillboard(com);
		sw->EndDraw(com);
	}
	if (rayF123) {
		
		sk->StreamOutput(com);//update
		sk1->StreamOutput(com);//update
		bil->StreamOutputBillboard(com);//update
		soto->StreamOutput(com);
		pd[0].StreamOutput(com);//update
		pd[1].StreamOutput(com);
		pdbl[0].StreamOutput(com);
		pdbl[1].StreamOutput(com);
		pd[2].StreamOutput(com);
		pd[3].StreamOutput(com);
		md->StreamOutput(com);
		gr->StreamOutput(com);//update
		wav->StreamOutput(com);//update
		d->End();
	}
	else {
		d->End();
	}
	
}

void UpdateDxrDivideBuffer() {
	sk->UpdateDxrDivideBuffer();
	pd[0].UpdateDxrDivideBuffer();
	wav->UpdateDxrDivideBuffer();
	gr->UpdateDxrDivideBuffer();
}

void AS() {
	int com = 2;
	if (rayF123) {
		Dx_CommandListObj* d = Dx_CommandManager::GetInstance()->getGraphicsComListObj(com);
		d->Bigin();
		dxr->update_g(com, 6);
		d->End();
	}
}

void raytrace() {
	int com = 3;
	if (rayF123) {
		Dx_CommandListObj* d = Dx_CommandManager::GetInstance()->getComputeComListObj(com);
		d->Bigin();
		dxr->raytrace_c(com);
		d->End();
	}
}
