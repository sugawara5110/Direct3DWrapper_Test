///////////////////////////////////////////////SkinObj/////////////////////////////////////////////////////

#ifndef Class_SkinObj_Header
#define Class_SkinObj_Header

#include "../../../../Common/Direct3DWrapper/Dx12Process.h"
#include "../../../../Common/DirectInputWrapper/DxInput.h"
#include "../../../../T_float/T_float.h"

class SkinObj {

private:
	std::unique_ptr<SkinMesh> sk = nullptr;
	CoordTf::VECTOR3 pos = {};
	float theta = 0.0f;
	int meshIndex = 0;
	int internalIndex = 0;

public:
	void create();
	void update();
	void Draw(int comNo);
	void StreamOutput(int comNo);
	ParameterDXR* getParameterDXR(int index);
	int getNumParameterDXR();
};

#endif