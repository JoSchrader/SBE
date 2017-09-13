#pragma once
#include "..\SBE_Internal.h"
#include "Model_f3fPc3fN2sT.h"
#include "Model_i3fP3fN2fT.h"
#include "Loaders\FileOperations.h"

#include <vector>

SBR::f3fPc3fN2sT::ModelPart::ModelPart()
{
	this->vertexes = nullptr;
	this->amountOfVertexes = 0;
	this->name = nullptr;
	this->dataIsContinous = false;
}

SBR::f3fPc3fN2sT::ModelPart::~ModelPart()
{
	if (!dataIsContinous)
	{
		free(this->vertexes);
		free(this->name);
	}
}

void  SBR::f3fPc3fN2sT::ModelPart::Load(char* buffer, bool copyDynamicData)
{
	SBR::f3fPc3fN2sT::ModelPartHeader* header = (SBR::f3fPc3fN2sT::ModelPartHeader*) buffer;

	this->amountOfVertexes = header->amountOfVertexes;
	this->name = buffer + header->nameOffset;
	this->vertexes = (SBR::f3fPc3fN2sT::CompressedVertex*) (buffer + header->vertexDataOffset);

	if (copyDynamicData)
	{
		this->dataIsContinous = false;
		
		SBR::f3fPc3fN2sT::CompressedVertex* _vertexes = (SBR::f3fPc3fN2sT::CompressedVertex*) malloc(sizeof(SBR::f3fPc3fN2sT::CompressedVertex) * header->amountOfVertexes);
		memcpy(_vertexes, this->vertexes, sizeof(SBR::f3fPc3fN2sT::CompressedVertex) * header->amountOfVertexes);
		this->vertexes = _vertexes;

		char* _name = (char*)malloc(strlen(this->name) + 1);
		strcpy(_name, this->name);
		this->name = _name;
	}
	else
	{
		this->dataIsContinous = true;
	}
}

int SBR::f3fPc3fN2sT::ModelPart::GetSize()
{
	int size = 0;
	size += sizeof(SBR::f3fPc3fN2sT::ModelPartHeader);
	size += (int)strlen(name) + 1;
	size += sizeof(SBR::f3fPc3fN2sT::CompressedVertex) * this->amountOfVertexes;
	return size;
}

void SBR::f3fPc3fN2sT::ModelPart::Save(char* buffer)
{
	SBR::f3fPc3fN2sT::ModelPartHeader* header = (SBR::f3fPc3fN2sT::ModelPartHeader*) buffer;

	header->modelType = SBR::ModelType::f3fPc3fN2sT_ID;
	header->amountOfVertexes = this->amountOfVertexes;

	char* curBufferPointer = buffer + sizeof(SBR::f3fPc3fN2sT::ModelPartHeader);

	strcpy(curBufferPointer, this->name);
	header->nameOffset = (int)(curBufferPointer - buffer);
	curBufferPointer += strlen(this->name) + 1;

	memcpy(curBufferPointer, this->vertexes, sizeof(SBR::f3fPc3fN2sT::CompressedVertex) * this->amountOfVertexes);
	header->vertexDataOffset = (int)(curBufferPointer - buffer);
	curBufferPointer += sizeof(SBR::f3fPc3fN2sT::CompressedVertex) * this->amountOfVertexes;
}

SBR::f3fPc3fN2sT::Model::Model()
{
	this->name = nullptr;
	this->amountOfParts = -1;
	this->parts = nullptr;
	this->dataIsContinous = false;
	this->continousDynamicData = nullptr;
}

SBR::f3fPc3fN2sT::Model::Model(SBR::i3fP3fN2fT::Model* model)
{
	this->continousDynamicData = nullptr;
	this->dataIsContinous = false;

	this->name = (char*)malloc(strlen(model->name) + 1);
	strcpy(this->name, model->name);

	this->amountOfParts = model->amountOfParts;
	this->parts = (SBR::f3fPc3fN2sT::ModelPart*) malloc(sizeof(SBR::f3fPc3fN2sT::ModelPart) * model->amountOfParts);

	std::vector<SBR::f3fPc3fN2sT::CompressedVertex> vertexData;

	SBM::Vector3* posData = model->meshData.positionData;
	SBM::Vector3* normalData = model->meshData.normalData;
	SBM::Vector2* uvData = model->meshData.uvData;

	for (int i = 0; i < this->amountOfParts; i++)
	{
		new (this->parts + i) SBR::f3fPc3fN2sT::ModelPart();
		this->parts[i].amountOfVertexes = model->parts[i].amountOfTriangles * 3;
		this->parts[i].dataIsContinous = false;

		this->parts[i].name = (char*)malloc(strlen(model->parts[i].name) + 1);
		strcpy(this->parts[i].name, model->parts[i].name);		

		SBR::i3fP3fN2fT::TriangleIndexData* indexData = model->parts[i].triangles;	
		int amountOfTriangles = model->parts[i].amountOfTriangles;

		for (int j = 0; j < amountOfTriangles; j++, indexData++)
		{			
			vertexData.push_back(SBR::f3fPc3fN2sT::CompressedVertex(posData[indexData->position1], normalData[indexData->normal1], uvData[indexData->texture1]));
			vertexData.push_back(SBR::f3fPc3fN2sT::CompressedVertex(posData[indexData->position2], normalData[indexData->normal2], uvData[indexData->texture2]));
			vertexData.push_back(SBR::f3fPc3fN2sT::CompressedVertex(posData[indexData->position3], normalData[indexData->normal3], uvData[indexData->texture3]));
		}

		this->parts[i].vertexes = (SBR::f3fPc3fN2sT::CompressedVertex*) malloc(sizeof(SBR::f3fPc3fN2sT::CompressedVertex) * this->parts[i].amountOfVertexes);
		memcpy(this->parts[i].vertexes, &vertexData[0], sizeof(SBR::f3fPc3fN2sT::CompressedVertex) * this->parts[i].amountOfVertexes);

		vertexData.clear();
	}
}

SBR::f3fPc3fN2sT::ModelPart * SBR::f3fPc3fN2sT::Model::MergeParts()
{
	SBR::f3fPc3fN2sT::ModelPart* modelPart = new SBR::f3fPc3fN2sT::ModelPart();

	int amountOfVertecis = 0;
	for (int i = 0; i < this->amountOfParts; i++)
	{
		amountOfVertecis += this->parts[i].amountOfVertexes;
	}

	modelPart->amountOfVertexes = amountOfVertecis;
	modelPart->dataIsContinous = false;

	modelPart->name = (char*)malloc(strlen(this->name) + 1);
	strcpy(modelPart->name, this->name);

	modelPart->vertexes = (SBR::f3fPc3fN2sT::CompressedVertex*) malloc(sizeof(SBR::f3fPc3fN2sT::CompressedVertex) * amountOfVertecis);
	char* curPointer = (char*)modelPart->vertexes;
	for (int i = 0; i < this->amountOfParts; i++)
	{
		memcpy(curPointer, this->parts[i].vertexes, sizeof(SBR::f3fPc3fN2sT::CompressedVertex) * this->parts[i].amountOfVertexes);
		curPointer += sizeof(SBR::f3fPc3fN2sT::CompressedVertex) * this->parts[i].amountOfVertexes;
	}

	return modelPart;
}

SBR::f3fPc3fN2sT::Model::~Model()
{
	if (this->name != nullptr)
		free(this->name);

	if (this->dataIsContinous && this->continousDynamicData != nullptr)
		free(this->continousDynamicData);

	for (int i = 0; i < this->amountOfParts; i++)
	{
		(this->parts + i)->~ModelPart();
	}

	free(this->parts);
}

int SBR::f3fPc3fN2sT::Model::GetSize()
{
	int size = 0;
	size += sizeof(SBR::f3fPc3fN2sT::ModelHeader);
	size += (int)strlen(this->name) + 1;
	size += sizeof(int) * this->amountOfParts;
	for (int i = 0; i < this->amountOfParts; i++)
	{
		size += this->parts[i].GetSize();
	}
	return size;
}


SBR::f3fPc3fN2sT::Model* SBR::f3fPc3fN2sT::Model::LoadFromFile(char* path, bool copyDynamicData)
{
	if (!SBR::File::Exist(path))
		return nullptr;

	SBR::f3fPc3fN2sT::Model* model = new SBR::f3fPc3fN2sT::Model();

	int size = 0;
	char* buffer = SBR::File::Read(path, &size);

	model->LoadFromBuffer(buffer, copyDynamicData);

	if (copyDynamicData)
		free(buffer);
	else
		model->continousDynamicData = buffer;

	model->name = (char*)malloc(sizeof(char) * strlen(path) + 1);
	strcpy(model->name, path);

	return model;
}

void SBR::f3fPc3fN2sT::Model::LoadFromBuffer(char* buffer, bool copyDynamicData)
{
	SBR::f3fPc3fN2sT::ModelHeader* header = (SBR::f3fPc3fN2sT::ModelHeader*) buffer;

	if (header->magicNumber != SBE_MODEL_MAGIC_BYTES)
		return;

	if (header->modelType != SBR::ModelType::f3fPc3fN2sT_ID)
		return;

	this->amountOfParts = header->amountOfParts;

	this->name = buffer + header->nameOffset;

	int* partOffsets = (int*) (buffer + header->partOffsetsOffset);		

	if (copyDynamicData)
	{
		this->dataIsContinous = false;

		char* _name = (char*)malloc(strlen(this->name) + 1);
		strcpy(_name, this->name);
		this->name = _name;
	}
	else
	{
		this->dataIsContinous = true;
		this->continousDynamicData = buffer;
	}

	this->parts = (SBR::f3fPc3fN2sT::ModelPart*) malloc(sizeof(SBR::f3fPc3fN2sT::ModelPart) * this->amountOfParts);
	for (int i = 0; i < this->amountOfParts; i++)
	{
		new (this->parts + i) SBR::f3fPc3fN2sT::ModelPart();
		this->parts[i].Load(buffer + partOffsets[i], copyDynamicData);
	}
}


void SBR::f3fPc3fN2sT::Model::SaveToFile(char* path)
{
	int size = this->GetSize();
	char* buffer = (char*)malloc(size);
	this->SaveToBuffer(buffer);
	SBR::File::Write(path, buffer, size);
}

void SBR::f3fPc3fN2sT::Model::SaveToBuffer(char* buffer)
{
	SBR::f3fPc3fN2sT::ModelHeader* modelHeader = (SBR::f3fPc3fN2sT::ModelHeader*) buffer;
	modelHeader->magicNumber = SBE_MODEL_MAGIC_BYTES;
	modelHeader->modelType = SBR::ModelType::f3fPc3fN2sT_ID;
	modelHeader->amountOfParts = this->amountOfParts;

	char* curBufferPointer = buffer + sizeof(SBR::f3fPc3fN2sT::ModelHeader);

	strcpy(curBufferPointer, this->name);
	modelHeader->nameOffset = (int)(curBufferPointer - buffer);
	curBufferPointer += strlen(this->name) + 1;

	int* partOffsets = (int*)curBufferPointer;
	modelHeader->partOffsetsOffset = (int)(curBufferPointer - buffer);
	curBufferPointer += sizeof(int) * this->amountOfParts;

	for (int i = 0; i < this->amountOfParts; i++)
	{
		this->parts[i].Save(curBufferPointer);
		partOffsets[i] = (int)(curBufferPointer - buffer);
		curBufferPointer += this->parts[i].GetSize();
	}
}