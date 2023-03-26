#pragma once

#include <stdio.h>
#include <string.h> 
#include <math.h>

static void sort(int* srcArr, int srcSize) {

	//ソートする配列を分割
	int topSize = (int)(srcSize * 0.5f);
	int halfSize = srcSize - topSize;
	int* topArr = new int[topSize];
	int* halfArr = new int[halfSize];
	memcpy(topArr, srcArr, topSize * sizeof(int));
	memcpy(halfArr, &srcArr[topSize], halfSize * sizeof(int));

	//要素1になるまで再帰
	if (topSize > 1)sort(topArr, topSize);
	if (halfSize > 1)sort(halfArr, halfSize);

	int topIndex = 0;
	int halfIndex = 0;
	int srcIndex = 0;
	//分割した配列の比較
	//それぞれの配列は整列済みの為, 先頭から比較するだけ
	for (int i = 0; i < srcSize; i++) {
		if (topArr[topIndex] > halfArr[halfIndex]) {
			srcArr[i] = topArr[topIndex++];
			if (topSize <= topIndex) {
				srcIndex = i + 1;
				break;
			}
		}
		else {
			srcArr[i] = halfArr[halfIndex++];
			if (halfSize <= halfIndex) {
				srcIndex = i + 1;
				break;
			}
		}
	}

	//余った要素を格納
	if (topSize > topIndex) {
		for (int i = srcIndex; i < srcSize; i++) {
			srcArr[i] = topArr[topIndex++];
		}
	}
	if (halfSize > halfIndex) {
		for (int i = srcIndex; i < srcSize; i++) {
			srcArr[i] = halfArr[halfIndex++];
		}
	}

	delete[] topArr;
	delete[] halfArr;
}

//離散コサイン変換の実験
double IdctTable[64][64] = {};

void createDctTable() {
	const double pi = 3.141592654;
	const double inverseRoute2 = 0.707106781;
	for (int y = 0; y < 8; y++) {
		for (int x = 0; x < 8; x++) {
			int dstIndex = y * 8 + x;
			double ds = 0.0;
			for (int i = 0; i < 8; i++) {
				for (int j = 0; j < 8; j++) {
					int srcIndex = j * 8 + i;
					double ci = (i == 0) ? inverseRoute2 : 1;
					double cj = (j == 0) ? inverseRoute2 : 1;
					IdctTable[dstIndex][srcIndex] = ci * cj *
						cos((((double)x + 0.5) * i * pi) / 8) *
						cos((((double)y + 0.5) * j * pi) / 8);
				}
			}
		}
	}
}

void createIdctTable() {
	const double pi = 3.141592654;
	const double inverseRoute2 = 0.707106781;
	for (int y = 0; y < 8; y++) {
		for (int x = 0; x < 8; x++) {
			int dstIndex = y * 8 + x;
			double ds = 0.0;
			for (int i = 0; i < 8; i++) {
				for (int j = 0; j < 8; j++) {
					int srcIndex = j * 8 + i;
					double ci = (i == 0) ? inverseRoute2 : 1;
					double cj = (j == 0) ? inverseRoute2 : 1;
					IdctTable[dstIndex][srcIndex] = ci * cj *
						cos((((double)2 * x + 1) * i * pi) / 16) *
						cos((((double)2 * y + 1) * j * pi) / 16);
				}
			}
		}
	}
}

void inverseDCT(short* dst, short* src) {
	for (int y = 0; y < 8; y++) {
		for (int x = 0; x < 8; x++) {
			int dstIndex = y * 8 + x;
			double ds = 0.0;
			for (int i = 0; i < 8; i++) {
				for (int j = 0; j < 8; j++) {
					int srcIndex = j * 8 + i;
					ds += src[srcIndex] * IdctTable[dstIndex][srcIndex];
				}
			}
			dst[dstIndex] = (short)ds * 2;
		}
	}
}

void inverseDiscreteCosineTransfer(short* decomp, unsigned int size) {
	unsigned int loop = size / 64;
	unsigned int index = 0;
	short dst[64] = {};
	for (unsigned int i = 0; i < loop; i++) {
		inverseDCT(dst, &decomp[index]);
		memcpy(&decomp[index], dst, sizeof(short) * 64);
		index += 64;
	}
}
