// Magic Software, Inc.
// http://www.magic-software.com
// http://www.wild-magic.com
// Copyright (c) 2003.  All Rights Reserved
//
// The Wild Magic Library (WML) source code is supplied under the terms of
// the license agreement http://www.magic-software.com/License/WildMagic.pdf
// and may not be copied or disclosed except in accordance with the terms of
// that agreement.

#include "Portals.h"

Portals g_kTheApp;

//----------------------------------------------------------------------------
Portals::Portals ()
    :
    Application("Portals",0,0,640,480,ColorRGB(0.5f,0.0f,1.0f))
{
    m_bInitialized = false;
}
//----------------------------------------------------------------------------
void Portals::CreateCenterCube (TextureStatePtr& rspkFloor,
    TextureStatePtr& rspkCeiling, TextureStatePtr& rspkWall,
    TextureStatePtr& rspkPicture0, TextureStatePtr& rspkPicture1,
    TextureStatePtr& rspkPicture2, TextureStatePtr& rspkPicture3,
    Node*& rpkCube, Portal**& rapkPortal)
{
    rpkCube = new Node(7);

    // walls
    Vector3f* akVertex = new Vector3f[24];
    akVertex[ 0] = Vector3f(-1.0f,-1.0f,0.0f);
    akVertex[ 1] = Vector3f(+1.0f,-1.0f,0.0f);
    akVertex[ 2] = Vector3f(+1.0f,+1.0f,0.0f);
    akVertex[ 3] = Vector3f(-1.0f,+1.0f,0.0f);
    akVertex[ 4] = Vector3f(-1.0f,-1.0f,2.0f);
    akVertex[ 5] = Vector3f(+1.0f,-1.0f,2.0f);
    akVertex[ 6] = Vector3f(+1.0f,+1.0f,2.0f);
    akVertex[ 7] = Vector3f(-1.0f,+1.0f,2.0f);
    akVertex[ 8] = Vector3f(+0.5f,-1.0f,0.0f);
    akVertex[ 9] = Vector3f(+0.5f,-1.0f,1.5f);
    akVertex[10] = Vector3f(-0.5f,-1.0f,1.5f);
    akVertex[11] = Vector3f(-0.5f,-1.0f,0.0f);
    akVertex[12] = Vector3f(-0.5f,+1.0f,0.0f);
    akVertex[13] = Vector3f(-0.5f,+1.0f,1.5f);
    akVertex[14] = Vector3f(+0.5f,+1.0f,1.5f);
    akVertex[15] = Vector3f(+0.5f,+1.0f,0.0f);
    akVertex[16] = Vector3f(+1.0f,+0.5f,0.0f);
    akVertex[17] = Vector3f(+1.0f,+0.5f,1.5f);
    akVertex[18] = Vector3f(+1.0f,-0.5f,1.5f);
    akVertex[19] = Vector3f(+1.0f,-0.5f,0.0f);
    akVertex[20] = Vector3f(-1.0f,-0.5f,0.0f);
    akVertex[21] = Vector3f(-1.0f,-0.5f,1.5f);
    akVertex[22] = Vector3f(-1.0f,+0.5f,1.5f);
    akVertex[23] = Vector3f(-1.0f,+0.5f,0.0f);

    Vector2f* akTexture = new Vector2f[24];
    akTexture[ 0] = Vector2f(0.00f,0.00f);
    akTexture[ 1] = Vector2f(1.00f,0.00f);
    akTexture[ 2] = Vector2f(0.00f,0.00f);
    akTexture[ 3] = Vector2f(1.00f,0.00f);
    akTexture[ 4] = Vector2f(0.00f,1.00f);
    akTexture[ 5] = Vector2f(1.00f,1.00f);
    akTexture[ 6] = Vector2f(0.00f,1.00f);
    akTexture[ 7] = Vector2f(1.00f,1.00f);
    akTexture[ 8] = Vector2f(0.75f,0.00f);
    akTexture[ 9] = Vector2f(0.75f,0.75f);
    akTexture[10] = Vector2f(0.25f,0.75f);
    akTexture[11] = Vector2f(0.25f,0.00f);
    akTexture[12] = Vector2f(0.75f,0.00f);
    akTexture[13] = Vector2f(0.75f,0.75f);
    akTexture[14] = Vector2f(0.25f,0.75f);
    akTexture[15] = Vector2f(0.25f,0.00f);
    akTexture[16] = Vector2f(0.25f,0.00f);
    akTexture[17] = Vector2f(0.25f,0.75f);
    akTexture[18] = Vector2f(0.75f,0.75f);
    akTexture[19] = Vector2f(0.75f,0.00f);
    akTexture[20] = Vector2f(0.25f,0.00f);
    akTexture[21] = Vector2f(0.25f,0.75f);
    akTexture[22] = Vector2f(0.75f,0.75f);
    akTexture[23] = Vector2f(0.75f,0.00f);

    int* aiConnect = new int[72];
    aiConnect[ 0] =  1;  aiConnect[ 1] =  8;  aiConnect[ 2] =  9;
    aiConnect[ 3] =  1;  aiConnect[ 4] =  9;  aiConnect[ 5] =  5;
    aiConnect[ 6] =  5;  aiConnect[ 7] =  9;  aiConnect[ 8] =  4;
    aiConnect[ 9] =  9;  aiConnect[10] = 10;  aiConnect[11] =  4;
    aiConnect[12] = 10;  aiConnect[13] =  0;  aiConnect[14] =  4;
    aiConnect[15] = 11;  aiConnect[16] =  0;  aiConnect[17] = 10;
    aiConnect[18] =  3;  aiConnect[19] = 12;  aiConnect[20] = 13;
    aiConnect[21] =  3;  aiConnect[22] = 13;  aiConnect[23] =  7;
    aiConnect[24] =  7;  aiConnect[25] = 13;  aiConnect[26] =  6;
    aiConnect[27] = 13;  aiConnect[28] = 14;  aiConnect[29] =  6;
    aiConnect[30] = 14;  aiConnect[31] =  2;  aiConnect[32] =  6;
    aiConnect[33] = 15;  aiConnect[34] =  2;  aiConnect[35] = 14;
    aiConnect[36] =  2;  aiConnect[37] = 16;  aiConnect[38] = 17;
    aiConnect[39] =  2;  aiConnect[40] = 17;  aiConnect[41] =  6;
    aiConnect[42] =  6;  aiConnect[43] = 17;  aiConnect[44] =  5;
    aiConnect[45] = 17;  aiConnect[46] = 18;  aiConnect[47] =  5;
    aiConnect[48] = 18;  aiConnect[49] =  1;  aiConnect[50] =  5;
    aiConnect[51] = 19;  aiConnect[52] =  1;  aiConnect[53] = 18;
    aiConnect[54] =  0;  aiConnect[55] = 20;  aiConnect[56] = 21;
    aiConnect[57] =  0;  aiConnect[58] = 21;  aiConnect[59] =  4;
    aiConnect[60] =  4;  aiConnect[61] = 21;  aiConnect[62] =  7;
    aiConnect[63] = 21;  aiConnect[64] = 22;  aiConnect[65] =  7;
    aiConnect[66] = 22;  aiConnect[67] =  3;  aiConnect[68] =  7;
    aiConnect[69] = 23;  aiConnect[70] =  3;  aiConnect[71] = 22;

    TriMesh* pkMesh = new TriMesh(24,akVertex,NULL,NULL,akTexture,24,
        aiConnect);
    pkMesh->SetRenderState(rspkWall);

    rpkCube->AttachChild(pkMesh);

    // portals
    rapkPortal = new Portal*[4];

    Vector3f* akModelVertex = new Vector3f[4];
    akModelVertex[0] = akVertex[11];
    akModelVertex[1] = akVertex[10];
    akModelVertex[2] = akVertex[ 9];
    akModelVertex[3] = akVertex[ 8];
    rapkPortal[0] = new Portal(4,akModelVertex,0,true);

    akModelVertex = new Vector3f[4];
    akModelVertex[0] = akVertex[15];
    akModelVertex[1] = akVertex[14];
    akModelVertex[2] = akVertex[13];
    akModelVertex[3] = akVertex[12];
    rapkPortal[1] = new Portal(4,akModelVertex,0,true);

    akModelVertex = new Vector3f[4];
    akModelVertex[0] = akVertex[19];
    akModelVertex[1] = akVertex[18];
    akModelVertex[2] = akVertex[17];
    akModelVertex[3] = akVertex[16];
    rapkPortal[2] = new Portal(4,akModelVertex,0,true);

    akModelVertex = new Vector3f[4];
    akModelVertex[0] = akVertex[23];
    akModelVertex[1] = akVertex[22];
    akModelVertex[2] = akVertex[21];
    akModelVertex[3] = akVertex[20];
    rapkPortal[3] = new Portal(4,akModelVertex,0,true);

    // floor
    akVertex = new Vector3f[4];
    akVertex[0] = Vector3f(-1.0f,-1.0f,0.0f);
    akVertex[1] = Vector3f(+1.0f,-1.0f,0.0f);
    akVertex[2] = Vector3f(+1.0f,+1.0f,0.0f);
    akVertex[3] = Vector3f(-1.0f,+1.0f,0.0f);

    akTexture = new Vector2f[4];
    akTexture[0] = Vector2f(0.0f,0.0f);
    akTexture[1] = Vector2f(1.0f,0.0f);
    akTexture[2] = Vector2f(1.0f,1.0f);
    akTexture[3] = Vector2f(0.0f,1.0f);

    aiConnect = new int[6];
    aiConnect[0] = 0;  aiConnect[1] = 1;  aiConnect[2] = 2;
    aiConnect[3] = 0;  aiConnect[4] = 2;  aiConnect[5] = 3;

    pkMesh = new TriMesh(4,akVertex,NULL,NULL,akTexture,2,aiConnect);
    pkMesh->SetRenderState(rspkFloor);

    rpkCube->AttachChild(pkMesh);

    // ceiling
    akVertex = new Vector3f[4];
    akVertex[0] = Vector3f(-1.0f,-1.0f,2.0f);
    akVertex[1] = Vector3f(+1.0f,-1.0f,2.0f);
    akVertex[2] = Vector3f(+1.0f,+1.0f,2.0f);
    akVertex[3] = Vector3f(-1.0f,+1.0f,2.0f);

    akTexture = new Vector2f[4];
    akTexture[0] = Vector2f(0.0f,0.0f);
    akTexture[1] = Vector2f(1.0f,0.0f);
    akTexture[2] = Vector2f(1.0f,1.0f);
    akTexture[3] = Vector2f(0.0f,1.0f);

    aiConnect = new int[6];
    aiConnect[0] = 0;  aiConnect[1] = 2;  aiConnect[2] = 1;
    aiConnect[3] = 0;  aiConnect[4] = 3;  aiConnect[5] = 2;

    pkMesh = new TriMesh(4,akVertex,NULL,NULL,akTexture,2,aiConnect);
    pkMesh->SetRenderState(rspkCeiling);

    rpkCube->AttachChild(pkMesh);

    // object 0
    akVertex = new Vector3f[4];
    akVertex[0] = Vector3f(-0.875f,-0.625f,0.75f);
    akVertex[1] = Vector3f(-0.875f,-0.625f,1.10f);
    akVertex[2] = Vector3f(-0.625f,-0.875f,1.10f);
    akVertex[3] = Vector3f(-0.625f,-0.875f,0.75f);

    akTexture = new Vector2f[4];
    akTexture[0] = Vector2f(1.0f,0.0f);
    akTexture[1] = Vector2f(1.0f,1.0f);
    akTexture[2] = Vector2f(0.0f,1.0f);
    akTexture[3] = Vector2f(0.0f,0.0f);

    aiConnect = new int[6];
    aiConnect[0] = 0;  aiConnect[1] = 1;  aiConnect[2] = 2;
    aiConnect[3] = 0;  aiConnect[4] = 2;  aiConnect[5] = 3;

    pkMesh = new TriMesh(4,akVertex,NULL,NULL,akTexture,2,aiConnect);
    pkMesh->SetRenderState(rspkPicture0);

    rpkCube->AttachChild(pkMesh);

    // object 1
    akVertex = new Vector3f[4];
    akVertex[0] = Vector3f(+0.875f,+0.625f,0.75f);
    akVertex[1] = Vector3f(+0.875f,+0.625f,1.10f);
    akVertex[2] = Vector3f(+0.625f,+0.875f,1.10f);
    akVertex[3] = Vector3f(+0.625f,+0.875f,0.75f);

    akTexture = new Vector2f[4];
    akTexture[0] = Vector2f(1.0f,0.0f);
    akTexture[1] = Vector2f(1.0f,1.0f);
    akTexture[2] = Vector2f(0.0f,1.0f);
    akTexture[3] = Vector2f(0.0f,0.0f);

    aiConnect = new int[6];
    aiConnect[0] = 0;  aiConnect[1] = 1;  aiConnect[2] = 2;
    aiConnect[3] = 0;  aiConnect[4] = 2;  aiConnect[5] = 3;

    pkMesh = new TriMesh(4,akVertex,NULL,NULL,akTexture,2,aiConnect);
    pkMesh->SetRenderState(rspkPicture1);

    rpkCube->AttachChild(pkMesh);

    // object 2
    akVertex = new Vector3f[4];
    akVertex[0] = Vector3f(-0.625f,+0.875f,0.75f);
    akVertex[1] = Vector3f(-0.625f,+0.875f,1.10f);
    akVertex[2] = Vector3f(-0.875f,+0.625f,1.10f);
    akVertex[3] = Vector3f(-0.875f,+0.625f,0.75f);

    akTexture = new Vector2f[4];
    akTexture[0] = Vector2f(1.0f,0.0f);
    akTexture[1] = Vector2f(1.0f,1.0f);
    akTexture[2] = Vector2f(0.0f,1.0f);
    akTexture[3] = Vector2f(0.0f,0.0f);

    aiConnect = new int[6];
    aiConnect[0] = 0;  aiConnect[1] = 1;  aiConnect[2] = 2;
    aiConnect[3] = 0;  aiConnect[4] = 2;  aiConnect[5] = 3;

    pkMesh = new TriMesh(4,akVertex,NULL,NULL,akTexture,2,aiConnect);
    pkMesh->SetRenderState(rspkPicture2);

    rpkCube->AttachChild(pkMesh);

    // object 3
    akVertex = new Vector3f[4];
    akVertex[0] = Vector3f(+0.625f,-0.875f,0.75f);
    akVertex[1] = Vector3f(+0.625f,-0.875f,1.10f);
    akVertex[2] = Vector3f(+0.875f,-0.625f,1.10f);
    akVertex[3] = Vector3f(+0.875f,-0.625f,0.75f);

    akTexture = new Vector2f[4];
    akTexture[0] = Vector2f(1.0f,0.0f);
    akTexture[1] = Vector2f(1.0f,1.0f);
    akTexture[2] = Vector2f(0.0f,1.0f);
    akTexture[3] = Vector2f(0.0f,0.0f);

    aiConnect = new int[6];
    aiConnect[0] = 0;  aiConnect[1] = 1;  aiConnect[2] = 2;
    aiConnect[3] = 0;  aiConnect[4] = 2;  aiConnect[5] = 3;

    pkMesh = new TriMesh(4,akVertex,NULL,NULL,akTexture,2,aiConnect);
    pkMesh->SetRenderState(rspkPicture3);

    rpkCube->AttachChild(pkMesh);
}
//----------------------------------------------------------------------------
void Portals::CreateAxisConnector (TextureStatePtr& rspkFloor,
    TextureStatePtr& rspkCeiling, TextureStatePtr& rspkWall,
    Node*& rpkCube, Portal**& rapkPortal)
{
    rpkCube = new Node(3);

    // walls
    Vector3f* akVertex = new Vector3f[16];
    akVertex[ 0] = Vector3f(-1.0f,-1.0f,0.0f);
    akVertex[ 1] = Vector3f(+1.0f,-1.0f,0.0f);
    akVertex[ 2] = Vector3f(+1.0f,+1.0f,0.0f);
    akVertex[ 3] = Vector3f(-1.0f,+1.0f,0.0f);
    akVertex[ 4] = Vector3f(-1.0f,-1.0f,2.0f);
    akVertex[ 5] = Vector3f(+1.0f,-1.0f,2.0f);
    akVertex[ 6] = Vector3f(+1.0f,+1.0f,2.0f);
    akVertex[ 7] = Vector3f(-1.0f,+1.0f,2.0f);
    akVertex[ 8] = Vector3f(+0.5f,-1.0f,0.0f);
    akVertex[ 9] = Vector3f(+0.5f,-1.0f,1.5f);
    akVertex[10] = Vector3f(-0.5f,-1.0f,1.5f);
    akVertex[11] = Vector3f(-0.5f,-1.0f,0.0f);
    akVertex[12] = Vector3f(-0.5f,+1.0f,0.0f);
    akVertex[13] = Vector3f(-0.5f,+1.0f,1.5f);
    akVertex[14] = Vector3f(+0.5f,+1.0f,1.5f);
    akVertex[15] = Vector3f(+0.5f,+1.0f,0.0f);

    Vector2f* akTexture = new Vector2f[16];
    akTexture[ 0] = Vector2f(0.00f,0.00f);
    akTexture[ 1] = Vector2f(1.00f,0.00f);
    akTexture[ 2] = Vector2f(0.00f,0.00f);
    akTexture[ 3] = Vector2f(1.00f,0.00f);
    akTexture[ 4] = Vector2f(0.00f,1.00f);
    akTexture[ 5] = Vector2f(1.00f,1.00f);
    akTexture[ 6] = Vector2f(0.00f,1.00f);
    akTexture[ 7] = Vector2f(1.00f,1.00f);
    akTexture[ 8] = Vector2f(0.75f,0.00f);
    akTexture[ 9] = Vector2f(0.75f,0.75f);
    akTexture[10] = Vector2f(0.25f,0.75f);
    akTexture[11] = Vector2f(0.25f,0.00f);
    akTexture[12] = Vector2f(0.75f,0.00f);
    akTexture[13] = Vector2f(0.75f,0.75f);
    akTexture[14] = Vector2f(0.25f,0.75f);
    akTexture[15] = Vector2f(0.25f,0.00f);

    int* aiConnect = new int[48];
    aiConnect[ 0] =  1;  aiConnect[ 1] =  8;  aiConnect[ 2] =  9;
    aiConnect[ 3] =  1;  aiConnect[ 4] =  9;  aiConnect[ 5] =  5;
    aiConnect[ 6] =  5;  aiConnect[ 7] =  9;  aiConnect[ 8] =  4;
    aiConnect[ 9] =  9;  aiConnect[10] = 10;  aiConnect[11] =  4;
    aiConnect[12] = 10;  aiConnect[13] =  0;  aiConnect[14] =  4;
    aiConnect[15] = 11;  aiConnect[16] =  0;  aiConnect[17] = 10;
    aiConnect[18] =  3;  aiConnect[19] = 12;  aiConnect[20] = 13;
    aiConnect[21] =  3;  aiConnect[22] = 13;  aiConnect[23] =  7;
    aiConnect[24] =  7;  aiConnect[25] = 13;  aiConnect[26] =  6;
    aiConnect[27] = 13;  aiConnect[28] = 14;  aiConnect[29] =  6;
    aiConnect[30] = 14;  aiConnect[31] =  2;  aiConnect[32] =  6;
    aiConnect[33] = 15;  aiConnect[34] =  2;  aiConnect[35] = 14;
    aiConnect[36] =  0;  aiConnect[37] =  7;  aiConnect[38] =  4;
    aiConnect[39] =  0;  aiConnect[40] =  3;  aiConnect[41] =  7;
    aiConnect[42] =  2;  aiConnect[43] =  5;  aiConnect[44] =  6;
    aiConnect[45] =  2;  aiConnect[46] =  1;  aiConnect[47] =  5;

    TriMesh* pkMesh = new TriMesh(16,akVertex,NULL,NULL,akTexture,16,
        aiConnect);
    pkMesh->SetRenderState(rspkWall);

    rpkCube->AttachChild(pkMesh);

    // portals
    rapkPortal = new Portal*[2];

    Vector3f* akModelVertex = new Vector3f[4];
    akModelVertex[0] = akVertex[11];
    akModelVertex[1] = akVertex[10];
    akModelVertex[2] = akVertex[ 9];
    akModelVertex[3] = akVertex[ 8];
    rapkPortal[0] = new Portal(4,akModelVertex,0,true);

    akModelVertex = new Vector3f[4];
    akModelVertex[0] = akVertex[15];
    akModelVertex[1] = akVertex[14];
    akModelVertex[2] = akVertex[13];
    akModelVertex[3] = akVertex[12];
    rapkPortal[1] = new Portal(4,akModelVertex,0,true);

    // floor
    akVertex = new Vector3f[4];
    akVertex[0] = Vector3f(-1.0f,-1.0f,0.0f);
    akVertex[1] = Vector3f(+1.0f,-1.0f,0.0f);
    akVertex[2] = Vector3f(+1.0f,+1.0f,0.0f);
    akVertex[3] = Vector3f(-1.0f,+1.0f,0.0f);

    akTexture = new Vector2f[4];
    akTexture[0] = Vector2f(0.0f,0.0f);
    akTexture[1] = Vector2f(1.0f,0.0f);
    akTexture[2] = Vector2f(1.0f,1.0f);
    akTexture[3] = Vector2f(0.0f,1.0f);

    aiConnect = new int[6];
    aiConnect[0] = 0;  aiConnect[1] = 1;  aiConnect[2] = 2;
    aiConnect[3] = 0;  aiConnect[4] = 2;  aiConnect[5] = 3;

    pkMesh = new TriMesh(4,akVertex,NULL,NULL,akTexture,2,aiConnect);
    pkMesh->SetRenderState(rspkFloor);

    rpkCube->AttachChild(pkMesh);

    // ceiling
    akVertex = new Vector3f[4];
    akVertex[0] = Vector3f(-1.0f,-1.0f,2.0f);
    akVertex[1] = Vector3f(+1.0f,-1.0f,2.0f);
    akVertex[2] = Vector3f(+1.0f,+1.0f,2.0f);
    akVertex[3] = Vector3f(-1.0f,+1.0f,2.0f);

    akTexture = new Vector2f[4];
    akTexture[0] = Vector2f(0.0f,0.0f);
    akTexture[1] = Vector2f(1.0f,0.0f);
    akTexture[2] = Vector2f(1.0f,1.0f);
    akTexture[3] = Vector2f(0.0f,1.0f);

    aiConnect = new int[6];
    aiConnect[0] = 0;  aiConnect[1] = 2;  aiConnect[2] = 1;
    aiConnect[3] = 0;  aiConnect[4] = 3;  aiConnect[5] = 2;

    pkMesh = new TriMesh(4,akVertex,NULL,NULL,akTexture,2,aiConnect);
    pkMesh->SetRenderState(rspkCeiling);

    rpkCube->AttachChild(pkMesh);
}
//----------------------------------------------------------------------------
void Portals::CreateEndCube (TextureStatePtr& rspkFloor,
    TextureStatePtr& rspkCeiling, TextureStatePtr& rspkWall,
    Node*& rpkCube, Portal**& rapkPortal)
{
    rpkCube = new Node(3);

    // walls
    Vector3f* akVertex = new Vector3f[20];
    akVertex[ 0] = Vector3f(-1.0f,-1.0f,0.0f);
    akVertex[ 1] = Vector3f(+1.0f,-1.0f,0.0f);
    akVertex[ 2] = Vector3f(+1.0f,+1.0f,0.0f);
    akVertex[ 3] = Vector3f(-1.0f,+1.0f,0.0f);
    akVertex[ 4] = Vector3f(-1.0f,-1.0f,2.0f);
    akVertex[ 5] = Vector3f(+1.0f,-1.0f,2.0f);
    akVertex[ 6] = Vector3f(+1.0f,+1.0f,2.0f);
    akVertex[ 7] = Vector3f(-1.0f,+1.0f,2.0f);
    akVertex[ 8] = Vector3f(+0.5f,-1.0f,0.0f);
    akVertex[ 9] = Vector3f(+0.5f,-1.0f,1.5f);
    akVertex[10] = Vector3f(-0.5f,-1.0f,1.5f);
    akVertex[11] = Vector3f(-0.5f,-1.0f,0.0f);
    akVertex[12] = Vector3f(-0.5f,+1.0f,0.0f);
    akVertex[13] = Vector3f(-0.5f,+1.0f,1.5f);
    akVertex[14] = Vector3f(+0.5f,+1.0f,1.5f);
    akVertex[15] = Vector3f(+0.5f,+1.0f,0.0f);
    akVertex[16] = Vector3f(+1.0f,+0.5f,0.0f);
    akVertex[17] = Vector3f(+1.0f,+0.5f,1.5f);
    akVertex[18] = Vector3f(+1.0f,-0.5f,1.5f);
    akVertex[19] = Vector3f(+1.0f,-0.5f,0.0f);

    Vector2f* akTexture = new Vector2f[20];
    akTexture[ 0] = Vector2f(0.00f,0.00f);
    akTexture[ 1] = Vector2f(1.00f,0.00f);
    akTexture[ 2] = Vector2f(0.00f,0.00f);
    akTexture[ 3] = Vector2f(1.00f,0.00f);
    akTexture[ 4] = Vector2f(0.00f,1.00f);
    akTexture[ 5] = Vector2f(1.00f,1.00f);
    akTexture[ 6] = Vector2f(0.00f,1.00f);
    akTexture[ 7] = Vector2f(1.00f,1.00f);
    akTexture[ 8] = Vector2f(0.75f,0.00f);
    akTexture[ 9] = Vector2f(0.75f,0.75f);
    akTexture[10] = Vector2f(0.25f,0.75f);
    akTexture[11] = Vector2f(0.25f,0.00f);
    akTexture[12] = Vector2f(0.75f,0.00f);
    akTexture[13] = Vector2f(0.75f,0.75f);
    akTexture[14] = Vector2f(0.25f,0.75f);
    akTexture[15] = Vector2f(0.25f,0.00f);
    akTexture[16] = Vector2f(0.25f,0.00f);
    akTexture[17] = Vector2f(0.25f,0.75f);
    akTexture[18] = Vector2f(0.75f,0.75f);
    akTexture[19] = Vector2f(0.75f,0.00f);

    int* aiConnect = new int[60];
    aiConnect[ 0] =  1;  aiConnect[ 1] =  8;  aiConnect[ 2] =  9;
    aiConnect[ 3] =  1;  aiConnect[ 4] =  9;  aiConnect[ 5] =  5;
    aiConnect[ 6] =  5;  aiConnect[ 7] =  9;  aiConnect[ 8] =  4;
    aiConnect[ 9] =  9;  aiConnect[10] = 10;  aiConnect[11] =  4;
    aiConnect[12] = 10;  aiConnect[13] =  0;  aiConnect[14] =  4;
    aiConnect[15] = 11;  aiConnect[16] =  0;  aiConnect[17] = 10;
    aiConnect[18] =  3;  aiConnect[19] = 12;  aiConnect[20] = 13;
    aiConnect[21] =  3;  aiConnect[22] = 13;  aiConnect[23] =  7;
    aiConnect[24] =  7;  aiConnect[25] = 13;  aiConnect[26] =  6;
    aiConnect[27] = 13;  aiConnect[28] = 14;  aiConnect[29] =  6;
    aiConnect[30] = 14;  aiConnect[31] =  2;  aiConnect[32] =  6;
    aiConnect[33] = 15;  aiConnect[34] =  2;  aiConnect[35] = 14;
    aiConnect[36] =  2;  aiConnect[37] = 16;  aiConnect[38] = 17;
    aiConnect[39] =  2;  aiConnect[40] = 17;  aiConnect[41] =  6;
    aiConnect[42] =  6;  aiConnect[43] = 17;  aiConnect[44] =  5;
    aiConnect[45] = 17;  aiConnect[46] = 18;  aiConnect[47] =  5;
    aiConnect[48] = 18;  aiConnect[49] =  1;  aiConnect[50] =  5;
    aiConnect[51] = 19;  aiConnect[52] =  1;  aiConnect[53] = 18;
    aiConnect[54] =  0;  aiConnect[55] =  7;  aiConnect[56] =  4;
    aiConnect[57] =  0;  aiConnect[58] =  3;  aiConnect[59] =  7;

    TriMesh* pkMesh = new TriMesh(20,akVertex,NULL,NULL,akTexture,20,
        aiConnect);
    pkMesh->SetRenderState(rspkWall);

    rpkCube->AttachChild(pkMesh);

    // portals
    rapkPortal = new Portal*[3];

    Vector3f* akModelVertex = new Vector3f[4];
    akModelVertex[0] = akVertex[11];
    akModelVertex[1] = akVertex[10];
    akModelVertex[2] = akVertex[ 9];
    akModelVertex[3] = akVertex[ 8];
    rapkPortal[0] = new Portal(4,akModelVertex,0,true);

    akModelVertex = new Vector3f[4];
    akModelVertex[0] = akVertex[15];
    akModelVertex[1] = akVertex[14];
    akModelVertex[2] = akVertex[13];
    akModelVertex[3] = akVertex[12];
    rapkPortal[1] = new Portal(4,akModelVertex,0,true);

    akModelVertex = new Vector3f[4];
    akModelVertex[0] = akVertex[19];
    akModelVertex[1] = akVertex[18];
    akModelVertex[2] = akVertex[17];
    akModelVertex[3] = akVertex[16];
    rapkPortal[2] = new Portal(4,akModelVertex,0,true);

    // floor
    akVertex = new Vector3f[4];
    akVertex[0] = Vector3f(-1.0f,-1.0f,0.0f);
    akVertex[1] = Vector3f(+1.0f,-1.0f,0.0f);
    akVertex[2] = Vector3f(+1.0f,+1.0f,0.0f);
    akVertex[3] = Vector3f(-1.0f,+1.0f,0.0f);

    akTexture = new Vector2f[4];
    akTexture[0] = Vector2f(0.0f,0.0f);
    akTexture[1] = Vector2f(1.0f,0.0f);
    akTexture[2] = Vector2f(1.0f,1.0f);
    akTexture[3] = Vector2f(0.0f,1.0f);

    aiConnect = new int[6];
    aiConnect[0] = 0;  aiConnect[1] = 1;  aiConnect[2] = 2;
    aiConnect[3] = 0;  aiConnect[4] = 2;  aiConnect[5] = 3;

    pkMesh = new TriMesh(4,akVertex,NULL,NULL,akTexture,2,aiConnect);
    pkMesh->SetRenderState(rspkFloor);

    rpkCube->AttachChild(pkMesh);

    // ceiling
    akVertex = new Vector3f[4];
    akVertex[0] = Vector3f(-1.0f,-1.0f,2.0f);
    akVertex[1] = Vector3f(+1.0f,-1.0f,2.0f);
    akVertex[2] = Vector3f(+1.0f,+1.0f,2.0f);
    akVertex[3] = Vector3f(-1.0f,+1.0f,2.0f);

    akTexture = new Vector2f[4];
    akTexture[0] = Vector2f(0.0f,0.0f);
    akTexture[1] = Vector2f(1.0f,0.0f);
    akTexture[2] = Vector2f(1.0f,1.0f);
    akTexture[3] = Vector2f(0.0f,1.0f);

    aiConnect = new int[6];
    aiConnect[0] = 0;  aiConnect[1] = 2;  aiConnect[2] = 1;
    aiConnect[3] = 0;  aiConnect[4] = 3;  aiConnect[5] = 2;

    pkMesh = new TriMesh(4,akVertex,NULL,NULL,akTexture,2,aiConnect);
    pkMesh->SetRenderState(rspkCeiling);

    rpkCube->AttachChild(pkMesh);
}
//----------------------------------------------------------------------------
void Portals::CreateDiagonalConnector (TextureStatePtr& rspkFloor,
    TextureStatePtr& rspkCeiling, TextureStatePtr& rspkWall,
    Node*& rpkCube, Portal**& rapkPortal)
{
    rpkCube = new Node(3);

    // walls
    Vector3f* akVertex = new Vector3f[16];
    akVertex[ 0] = Vector3f(3.0f,1.0f,0.0f);
    akVertex[ 1] = Vector3f(5.0f,1.0f,0.0f);
    akVertex[ 2] = Vector3f(1.0f,5.0f,0.0f);
    akVertex[ 3] = Vector3f(1.0f,3.0f,0.0f);
    akVertex[ 4] = Vector3f(3.0f,1.0f,2.0f);
    akVertex[ 5] = Vector3f(5.0f,1.0f,2.0f);
    akVertex[ 6] = Vector3f(1.0f,5.0f,2.0f);
    akVertex[ 7] = Vector3f(1.0f,3.0f,2.0f);
    akVertex[ 8] = Vector3f(4.5f,1.0f,0.0f);
    akVertex[ 9] = Vector3f(4.5f,1.0f,1.5f);
    akVertex[10] = Vector3f(3.5f,1.0f,1.5f);
    akVertex[11] = Vector3f(3.5f,1.0f,0.0f);
    akVertex[12] = Vector3f(1.0f,3.5f,0.0f);
    akVertex[13] = Vector3f(1.0f,3.5f,1.5f);
    akVertex[14] = Vector3f(1.0f,4.5f,1.5f);
    akVertex[15] = Vector3f(1.0f,4.5f,0.0f);

    Vector2f* akTexture = new Vector2f[16];
    akTexture[ 0] = Vector2f(0.00f,0.00f);
    akTexture[ 1] = Vector2f(1.00f,0.00f);
    akTexture[ 2] = Vector2f(0.00f,0.00f);
    akTexture[ 3] = Vector2f(1.00f,0.00f);
    akTexture[ 4] = Vector2f(0.00f,1.00f);
    akTexture[ 5] = Vector2f(1.00f,1.00f);
    akTexture[ 6] = Vector2f(0.00f,1.00f);
    akTexture[ 7] = Vector2f(1.00f,1.00f);
    akTexture[ 8] = Vector2f(0.75f,0.00f);
    akTexture[ 9] = Vector2f(0.75f,0.75f);
    akTexture[10] = Vector2f(0.25f,0.75f);
    akTexture[11] = Vector2f(0.25f,0.00f);
    akTexture[12] = Vector2f(0.75f,0.00f);
    akTexture[13] = Vector2f(0.75f,0.75f);
    akTexture[14] = Vector2f(0.25f,0.75f);
    akTexture[15] = Vector2f(0.25f,0.00f);

    int* aiConnect = new int[48];
    aiConnect[ 0] =  1;  aiConnect[ 1] =  8;  aiConnect[ 2] =  9;
    aiConnect[ 3] =  1;  aiConnect[ 4] =  9;  aiConnect[ 5] =  5;
    aiConnect[ 6] =  5;  aiConnect[ 7] =  9;  aiConnect[ 8] =  4;
    aiConnect[ 9] =  9;  aiConnect[10] = 10;  aiConnect[11] =  4;
    aiConnect[12] = 10;  aiConnect[13] =  0;  aiConnect[14] =  4;
    aiConnect[15] = 11;  aiConnect[16] =  0;  aiConnect[17] = 10;
    aiConnect[18] =  3;  aiConnect[19] = 12;  aiConnect[20] = 13;
    aiConnect[21] =  3;  aiConnect[22] = 13;  aiConnect[23] =  7;
    aiConnect[24] =  7;  aiConnect[25] = 13;  aiConnect[26] =  6;
    aiConnect[27] = 13;  aiConnect[28] = 14;  aiConnect[29] =  6;
    aiConnect[30] = 14;  aiConnect[31] =  2;  aiConnect[32] =  6;
    aiConnect[33] = 15;  aiConnect[34] =  2;  aiConnect[35] = 14;
    aiConnect[36] =  0;  aiConnect[37] =  7;  aiConnect[38] =  4;
    aiConnect[39] =  0;  aiConnect[40] =  3;  aiConnect[41] =  7;
    aiConnect[42] =  2;  aiConnect[43] =  5;  aiConnect[44] =  6;
    aiConnect[45] =  2;  aiConnect[46] =  1;  aiConnect[47] =  5;

    TriMesh* pkMesh = new TriMesh(16,akVertex,NULL,NULL,akTexture,16,
        aiConnect);
    pkMesh->SetRenderState(rspkWall);

    rpkCube->AttachChild(pkMesh);

    // portals
    rapkPortal = new Portal*[2];

    Vector3f* akModelVertex = new Vector3f[4];
    akModelVertex[0] = akVertex[11];
    akModelVertex[1] = akVertex[10];
    akModelVertex[2] = akVertex[ 9];
    akModelVertex[3] = akVertex[ 8];
    rapkPortal[0] = new Portal(4,akModelVertex,0,true);

    akModelVertex = new Vector3f[4];
    akModelVertex[0] = akVertex[15];
    akModelVertex[1] = akVertex[14];
    akModelVertex[2] = akVertex[13];
    akModelVertex[3] = akVertex[12];
    rapkPortal[1] = new Portal(4,akModelVertex,0,true);

    // floor
    akVertex = new Vector3f[4];
    akVertex[0] = Vector3f(3.0f,1.0f,0.0f);
    akVertex[1] = Vector3f(5.0f,1.0f,0.0f);
    akVertex[2] = Vector3f(1.0f,5.0f,0.0f);
    akVertex[3] = Vector3f(1.0f,3.0f,0.0f);

    akTexture = new Vector2f[4];
    akTexture[0] = Vector2f(0.0f,0.0f);
    akTexture[1] = Vector2f(1.0f,0.0f);
    akTexture[2] = Vector2f(1.0f,1.0f);
    akTexture[3] = Vector2f(0.0f,1.0f);

    aiConnect = new int[6];
    aiConnect[0] = 0;  aiConnect[1] = 1;  aiConnect[2] = 2;
    aiConnect[3] = 0;  aiConnect[4] = 2;  aiConnect[5] = 3;

    pkMesh = new TriMesh(4,akVertex,NULL,NULL,akTexture,2,aiConnect);
    pkMesh->SetRenderState(rspkFloor);

    rpkCube->AttachChild(pkMesh);

    // ceiling
    akVertex = new Vector3f[4];
    akVertex[0] = Vector3f(3.0f,1.0f,2.0f);
    akVertex[1] = Vector3f(5.0f,1.0f,2.0f);
    akVertex[2] = Vector3f(1.0f,5.0f,2.0f);
    akVertex[3] = Vector3f(1.0f,3.0f,2.0f);

    akTexture = new Vector2f[4];
    akTexture[0] = Vector2f(0.0f,0.0f);
    akTexture[1] = Vector2f(1.0f,0.0f);
    akTexture[2] = Vector2f(1.0f,1.0f);
    akTexture[3] = Vector2f(0.0f,1.0f);

    aiConnect = new int[6];
    aiConnect[0] = 0;  aiConnect[1] = 2;  aiConnect[2] = 1;
    aiConnect[3] = 0;  aiConnect[4] = 3;  aiConnect[5] = 2;

    pkMesh = new TriMesh(4,akVertex,NULL,NULL,akTexture,2,aiConnect);
    pkMesh->SetRenderState(rspkCeiling);

    rpkCube->AttachChild(pkMesh);
}
//----------------------------------------------------------------------------
TriMesh* Portals::CreateOutside ()
{
    const int iVertexQuantity = 40;
    Vector3f* akVertex = new Vector3f[iVertexQuantity];
    akVertex[0] = Vector3f(-1.0f,-1.0f,2.0f);
    akVertex[1] = Vector3f(+1.0f,-1.0f,2.0f);
    akVertex[2] = Vector3f(+1.0f,+1.0f,2.0f);
    akVertex[3] = Vector3f(-1.0f,+1.0f,2.0f);
    akVertex[4] = Vector3f(-1.0f,-1.0f,0.0f);
    akVertex[5] = Vector3f(+1.0f,-1.0f,0.0f);
    akVertex[6] = Vector3f(+1.0f,+1.0f,0.0f);
    akVertex[7] = Vector3f(-1.0f,+1.0f,0.0f);

    Vector3f kTrn(4.0f,0.0f,0.0f);
    int i, j;
    for (i = 0, j = 8; i < 8; i++, j++)
        akVertex[j] = akVertex[i] + kTrn;

    kTrn = Vector3f(0.0f,4.0f,0.0f);
    for (i = 0, j = 16; i < 8; i++, j++)
        akVertex[j] = akVertex[i] + kTrn;

    kTrn = Vector3f(-4.0f,0.0f,0.0f);
    for (i = 0, j = 24; i < 8; i++, j++)
        akVertex[j] = akVertex[i] + kTrn;

    kTrn = Vector3f(0.0f,-4.0f,0.0f);
    for (i = 0, j = 32; i < 8; i++, j++)
        akVertex[j] = akVertex[i] + kTrn;

    ColorRGB* akColor = new ColorRGB[iVertexQuantity];
    for (i = 0; i < iVertexQuantity; i++)
    {
        akColor[i].r = Mathf::UnitRandom();
        akColor[i].g = Mathf::UnitRandom();
        akColor[i].b = Mathf::UnitRandom();
    }

    const int iTriangleQuantity = 92;
    int* aiConnect = new int[3*iTriangleQuantity];
    aiConnect[ 0] =  0;  aiConnect[ 1] =  1;  aiConnect[ 2] =  2;
    aiConnect[ 3] =  0;  aiConnect[ 4] =  2;  aiConnect[ 5] =  3;
    aiConnect[ 6] =  1;  aiConnect[ 7] = 11;  aiConnect[ 8] =  2;
    aiConnect[ 9] =  1;  aiConnect[10] =  8;  aiConnect[11] = 11;
    aiConnect[12] =  8;  aiConnect[13] = 10;  aiConnect[14] = 11;
    aiConnect[15] =  8;  aiConnect[16] =  9;  aiConnect[17] = 10;
    aiConnect[18] = 25;  aiConnect[19] =  0;  aiConnect[20] =  3;
    aiConnect[21] = 25;  aiConnect[22] =  3;  aiConnect[23] = 26;
    aiConnect[24] = 24;  aiConnect[25] = 25;  aiConnect[26] = 26;
    aiConnect[27] = 24;  aiConnect[28] = 26;  aiConnect[29] = 27;
    aiConnect[30] =  3;  aiConnect[31] =  2;  aiConnect[32] = 17;
    aiConnect[33] =  3;  aiConnect[34] = 17;  aiConnect[35] = 16;
    aiConnect[36] = 16;  aiConnect[37] = 17;  aiConnect[38] = 18;
    aiConnect[39] = 16;  aiConnect[40] = 18;  aiConnect[41] = 19;
    aiConnect[42] = 35;  aiConnect[43] =  1;  aiConnect[44] =  0;
    aiConnect[45] = 35;  aiConnect[46] = 34;  aiConnect[47] =  1;
    aiConnect[48] = 32;  aiConnect[49] = 34;  aiConnect[50] = 35;
    aiConnect[51] = 32;  aiConnect[52] = 33;  aiConnect[53] = 34;
    aiConnect[54] = 27;  aiConnect[55] = 16;  aiConnect[56] = 19;
    aiConnect[57] = 27;  aiConnect[58] = 26;  aiConnect[59] = 16;
    aiConnect[60] = 17;  aiConnect[61] = 11;  aiConnect[62] = 18;
    aiConnect[63] = 18;  aiConnect[64] = 11;  aiConnect[65] = 10;
    aiConnect[66] = 24;  aiConnect[67] = 32;  aiConnect[68] = 25;
    aiConnect[69] = 25;  aiConnect[70] = 32;  aiConnect[71] = 35;
    aiConnect[72] = 34;  aiConnect[73] =  9;  aiConnect[74] =  8;
    aiConnect[75] = 34;  aiConnect[76] = 33;  aiConnect[77] =  9;

    for (i = 0, j = 78; i < 26; i++)
    {
        aiConnect[j++] = 4 + aiConnect[3*i];
        aiConnect[j++] = 4 + aiConnect[3*i+2];
        aiConnect[j++] = 4 + aiConnect[3*i+1];
    }

    aiConnect[156] =  6;  aiConnect[157] =  2;  aiConnect[158] = 11;
    aiConnect[159] =  6;  aiConnect[160] = 11;  aiConnect[161] = 15;
    aiConnect[162] = 21;  aiConnect[163] = 17;  aiConnect[164] =  2;
    aiConnect[165] = 21;  aiConnect[166] =  2;  aiConnect[167] =  6;
    aiConnect[168] = 15;  aiConnect[169] = 11;  aiConnect[170] = 17;
    aiConnect[171] = 15;  aiConnect[172] = 17;  aiConnect[173] = 21;
    aiConnect[174] = 12;  aiConnect[175] =  8;  aiConnect[176] =  1;
    aiConnect[177] = 12;  aiConnect[178] =  1;  aiConnect[179] =  5;
    aiConnect[180] =  5;  aiConnect[181] =  1;  aiConnect[182] = 34;
    aiConnect[183] =  5;  aiConnect[184] = 34;  aiConnect[185] = 38;
    aiConnect[186] = 38;  aiConnect[187] = 34;  aiConnect[188] =  8;
    aiConnect[189] = 38;  aiConnect[190] =  8;  aiConnect[191] = 12;
    aiConnect[192] =  4;  aiConnect[193] =  0;  aiConnect[194] = 25;
    aiConnect[195] =  4;  aiConnect[196] = 25;  aiConnect[197] = 29;
    aiConnect[198] = 39;  aiConnect[199] = 35;  aiConnect[200] =  0;
    aiConnect[201] = 39;  aiConnect[202] =  0;  aiConnect[203] =  4;
    aiConnect[204] = 29;  aiConnect[205] = 25;  aiConnect[206] = 35;
    aiConnect[207] = 29;  aiConnect[208] = 35;  aiConnect[209] = 39;
    aiConnect[210] =  7;  aiConnect[211] =  3;  aiConnect[212] = 16;
    aiConnect[213] =  7;  aiConnect[214] = 16;  aiConnect[215] = 20;
    aiConnect[216] = 30;  aiConnect[217] = 26;  aiConnect[218] =  3;
    aiConnect[219] = 30;  aiConnect[220] =  3;  aiConnect[221] =  7;
    aiConnect[222] = 20;  aiConnect[223] = 16;  aiConnect[224] = 26;
    aiConnect[225] = 20;  aiConnect[226] = 26;  aiConnect[227] = 30;
    aiConnect[228] = 14;  aiConnect[229] = 10;  aiConnect[230] =  9;
    aiConnect[231] = 14;  aiConnect[232] =  9;  aiConnect[233] = 13;
    aiConnect[234] = 22;  aiConnect[235] = 18;  aiConnect[236] = 10;
    aiConnect[237] = 22;  aiConnect[238] = 10;  aiConnect[239] = 14;
    aiConnect[240] = 23;  aiConnect[241] = 19;  aiConnect[242] = 18;
    aiConnect[243] = 23;  aiConnect[244] = 18;  aiConnect[245] = 22;
    aiConnect[246] = 31;  aiConnect[247] = 27;  aiConnect[248] = 19;
    aiConnect[249] = 31;  aiConnect[250] = 19;  aiConnect[251] = 23;
    aiConnect[252] = 28;  aiConnect[253] = 24;  aiConnect[254] = 27;
    aiConnect[255] = 28;  aiConnect[256] = 27;  aiConnect[257] = 31;
    aiConnect[258] = 36;  aiConnect[259] = 32;  aiConnect[260] = 24;
    aiConnect[261] = 36;  aiConnect[262] = 24;  aiConnect[263] = 28;
    aiConnect[264] = 37;  aiConnect[265] = 33;  aiConnect[266] = 32;
    aiConnect[267] = 37;  aiConnect[268] = 32;  aiConnect[269] = 36;
    aiConnect[270] = 13;  aiConnect[271] =  9;  aiConnect[272] = 33;
    aiConnect[273] = 13;  aiConnect[274] = 33;  aiConnect[275] = 37;

    TriMesh* pkMesh = new TriMesh(iVertexQuantity,akVertex,NULL,akColor,
        NULL,iTriangleQuantity,aiConnect);

    return pkMesh;
}
//----------------------------------------------------------------------------
ConvexRegionManager* Portals::CreateBspTree ()
{
    // construction of tree in BspTree.txt.
    ConvexRegionManager* pkC = new ConvexRegionManager(true);
    pkC->SetName("CRM");
    pkC->ModelPlane().Set(Vector3f(0.0f,0.0f,-1.0f),0.0f);

    BspNode* pkR = new BspNode;
    pkR->SetName("R");
    pkR->ModelPlane().Set(Vector3f(0.0f,0.0f,1.0f),2.0f);

    BspNode* pkRR = new BspNode;
    pkRR->SetName("RR");
    pkRR->ModelPlane().Set(Vector3f(1.0f,0.0f,0.0f),1.0f);

    BspNode* pkRRL = new BspNode;
    pkRRL->SetName("RRL");
    pkRRL->ModelPlane().Set(Vector3f(0.0f,1.0f,0.0f),1.0f);

    BspNode* pkRRLL = new BspNode;
    pkRRLL->SetName("RRLL");
    pkRRLL->ModelPlane().Set(Vector3f(1.0f,1.0f,0.0f),4.0f);

    BspNode* pkRRLLL = new BspNode;
    pkRRLLL->SetName("RRLLL");
    pkRRLLL->ModelPlane().Set(Vector3f(1.0f,1.0f,0.0f),6.0f);

    BspNode* pkRRLR = new BspNode;
    pkRRLR->SetName("RRLR");
    pkRRLR->ModelPlane().Set(Vector3f(0.0f,-1.0f,0.0f),1.0f);

    BspNode* pkRRLRL = new BspNode;
    pkRRLRL->SetName("RRLRL");
    pkRRLRL->ModelPlane().Set(Vector3f(1.0f,-1.0f,0.0f),4.0f);

    BspNode* pkRRLRLL = new BspNode;
    pkRRLRLL->SetName("RRLRLL");
    pkRRLRLL->ModelPlane().Set(Vector3f(1.0f,-1.0f,0.0f),6.0f);

    BspNode* pkRRLRR = new BspNode;
    pkRRLRR->SetName("RRLRR");
    pkRRLRR->ModelPlane().Set(Vector3f(1.0f,0.0f,0.0f),3.0f);

    BspNode* pkRRLRRL = new BspNode;
    pkRRLRRL->SetName("RRLRRL");
    pkRRLRRL->ModelPlane().Set(Vector3f(1.0f,0.0f,0.0f),5.0f);

    BspNode* pkRRR = new BspNode;
    pkRRR->SetName("RRR");
    pkRRR->ModelPlane().Set(Vector3f(-1.0f,0.0f,0.0f),1.0f);

    BspNode* pkRRRL = new BspNode;
    pkRRRL->SetName("RRRL");
    pkRRRL->ModelPlane().Set(Vector3f(0.0f,1.0f,0.0f),1.0f);

    BspNode* pkRRRLL = new BspNode;
    pkRRRLL->SetName("RRRLL");
    pkRRRLL->ModelPlane().Set(Vector3f(-1.0f,1.0f,0.0f),4.0f);

    BspNode* pkRRRLLL = new BspNode;
    pkRRRLLL->SetName("RRRLLL");
    pkRRRLLL->ModelPlane().Set(Vector3f(-1.0f,1.0f,0.0f),6.0f);

    BspNode* pkRRRLR = new BspNode;
    pkRRRLR->SetName("RRRLR");
    pkRRRLR->ModelPlane().Set(Vector3f(0.0f,-1.0f,0.0f),1.0f);

    BspNode* pkRRRLRL = new BspNode;
    pkRRRLRL->SetName("RRRLRL");
    pkRRRLRL->ModelPlane().Set(Vector3f(-1.0f,-1.0f,0.0f),4.0f);

    BspNode* pkRRRLRLL = new BspNode;
    pkRRRLRLL->SetName("RRRLRLL");
    pkRRRLRLL->ModelPlane().Set(Vector3f(-1.0f,-1.0f,0.0f),6.0f);

    BspNode* pkRRRLRR = new BspNode;
    pkRRRLRR->SetName("RRRLRR");
    pkRRRLRR->ModelPlane().Set(Vector3f(-1.0f,0.0f,0.0f),3.0f);

    BspNode* pkRRRLRRL = new BspNode;
    pkRRRLRRL->SetName("RRRLRRL");
    pkRRRLRRL->ModelPlane().Set(Vector3f(-1.0f,0.0f,0.0f),5.0f);

    BspNode* pkRRRR = new BspNode;
    pkRRRR->SetName("RRRR");
    pkRRRR->ModelPlane().Set(Vector3f(0.0f,1.0f,0.0f),1.0f);

    BspNode* pkRRRRL = new BspNode;
    pkRRRRL->SetName("RRRRL");
    pkRRRRL->ModelPlane().Set(Vector3f(0.0f,1.0f,0.0f),3.0f);

    BspNode* pkRRRRLL = new BspNode;
    pkRRRRLL->SetName("RRRRLL");
    pkRRRRLL->ModelPlane().Set(Vector3f(0.0f,1.0f,0.0f),5.0f);

    BspNode* pkRRRRR = new BspNode;
    pkRRRRR->SetName("RRRRR");
    pkRRRRR->ModelPlane().Set(Vector3f(0.0f,-1.0f,0.0f),1.0f);

    BspNode* pkRRRRRL = new BspNode;
    pkRRRRRL->SetName("RRRRRL");
    pkRRRRRL->ModelPlane().Set(Vector3f(0.0f,-1.0f,0.0f),3.0f);

    BspNode* pkRRRRRLL = new BspNode;
    pkRRRRRLL->SetName("RRRRRLL");
    pkRRRRRLL->ModelPlane().Set(Vector3f(0.0f,-1.0f,0.0f),5.0f);

    // create regions and portals
    Node* pkNode;
    Portal** apkPortal;

    CreateCenterCube(m_spkTextureSand,m_spkTextureSky,m_spkTextureAgate,
        m_spkTextureMunch,m_spkTextureBuff,m_spkTextureDave,
        m_spkTextureShelly,pkNode,apkPortal);
    ConvexRegion* pkC00 = new ConvexRegion(4,apkPortal,pkNode);
    pkC00->SetName("C00");

    CreateAxisConnector(m_spkTextureSand,m_spkTextureSky,
        m_spkTextureConnector,pkNode,apkPortal);
    ConvexRegion* pkC02 = new ConvexRegion(2,apkPortal,pkNode);
    pkC02->SetName("C02");
    pkC02->Translate() = Vector3f(0.0f,2.0f,0.0f);

    CreateAxisConnector(m_spkTextureSand,m_spkTextureSky,
        m_spkTextureConnector,pkNode,apkPortal);
    ConvexRegion* pkC0m2 = new ConvexRegion(2,apkPortal,pkNode);
    pkC0m2->SetName("C0m2");
    pkC0m2->Translate() = Vector3f(0.0f,-2.0f,0.0f);

    CreateAxisConnector(m_spkTextureSand,m_spkTextureSky,
        m_spkTextureConnector,pkNode,apkPortal);
    ConvexRegion* pkC20 = new ConvexRegion(2,apkPortal,pkNode);
    pkC20->SetName("C20");
    pkC20->Translate() = Vector3f(2.0f,0.0f,0.0f);
    pkC20->Rotate().FromAxisAngle(Vector3f::UNIT_Z,Mathf::HALF_PI);

    CreateAxisConnector(m_spkTextureSand,m_spkTextureSky,
        m_spkTextureConnector,pkNode,apkPortal);
    ConvexRegion* pkCm20 = new ConvexRegion(2,apkPortal,pkNode);
    pkCm20->SetName("Cm20");
    pkCm20->Translate() = Vector3f(-2.0f,0.0f,0.0f);
    pkCm20->Rotate().FromAxisAngle(Vector3f::UNIT_Z,Mathf::HALF_PI);

    CreateEndCube(m_spkTextureSand,m_spkTextureSky,m_spkTextureQuartz,pkNode,
        apkPortal);
    ConvexRegion* pkC04 = new ConvexRegion(3,apkPortal,pkNode);
    pkC04->SetName("C04");
    pkC04->Translate() = Vector3f(0.0f,4.0f,0.0f);
    pkC04->Rotate().FromAxisAngle(Vector3f::UNIT_Z,-Mathf::HALF_PI);

    CreateEndCube(m_spkTextureSand,m_spkTextureSky,m_spkTextureBark,pkNode,
        apkPortal);
    ConvexRegion* pkC0m4 = new ConvexRegion(3,apkPortal,pkNode);
    pkC0m4->SetName("C0m4");
    pkC0m4->Translate() = Vector3f(0.0f,-4.0f,0.0f);
    pkC0m4->Rotate().FromAxisAngle(Vector3f::UNIT_Z,Mathf::HALF_PI);

    CreateEndCube(m_spkTextureSand,m_spkTextureSky,m_spkTextureWater,pkNode,
        apkPortal);
    ConvexRegion* pkC40 = new ConvexRegion(3,apkPortal,pkNode);
    pkC40->SetName("C40");
    pkC40->Translate() = Vector3f(4.0f,0.0f,0.0f);
    pkC40->Rotate().FromAxisAngle(Vector3f::UNIT_Z,Mathf::PI);

    CreateEndCube(m_spkTextureSand,m_spkTextureSky,m_spkTexturePebbles,pkNode,
        apkPortal);
    ConvexRegion* pkCm40 = new ConvexRegion(3,apkPortal,pkNode);
    pkCm40->SetName("Cm40");
    pkCm40->Translate() = Vector3f(-4.0f,0.0f,0.0f);

    CreateDiagonalConnector(m_spkTextureSand,m_spkTextureSky,
        m_spkTextureConnector,pkNode,apkPortal);
    ConvexRegion* pkDPP = new ConvexRegion(2,apkPortal,pkNode);
    pkDPP->SetName("DPP");

    CreateDiagonalConnector(m_spkTextureSand,m_spkTextureSky,
        m_spkTextureConnector,pkNode,apkPortal);
    ConvexRegion* pkDMP = new ConvexRegion(2,apkPortal,pkNode);
    pkDMP->SetName("DMP");
    pkDMP->Rotate().FromAxisAngle(Vector3f::UNIT_Z,Mathf::HALF_PI);

    CreateDiagonalConnector(m_spkTextureSand,m_spkTextureSky,
        m_spkTextureConnector,pkNode,apkPortal);
    ConvexRegion* pkDMM = new ConvexRegion(2,apkPortal,pkNode);
    pkDMM->SetName("DMM");
    pkDMM->Rotate().FromAxisAngle(Vector3f::UNIT_Z,Mathf::PI);

    CreateDiagonalConnector(m_spkTextureSand,m_spkTextureSky,
        m_spkTextureConnector,pkNode,apkPortal);
    ConvexRegion* pkDPM = new ConvexRegion(2,apkPortal,pkNode);
    pkDPM->SetName("DPM");
    pkDPM->Rotate().FromAxisAngle(Vector3f::UNIT_Z,-Mathf::HALF_PI);

    // create adjacency graph
    pkC00->GetPortal(0)->AdjacentRegion() = pkC0m2;
    pkC00->GetPortal(1)->AdjacentRegion() = pkC02;
    pkC00->GetPortal(2)->AdjacentRegion() = pkC20;
    pkC00->GetPortal(3)->AdjacentRegion() = pkCm20;
    pkC02->GetPortal(0)->AdjacentRegion() = pkC00;
    pkC02->GetPortal(1)->AdjacentRegion() = pkC04;
    pkC0m2->GetPortal(0)->AdjacentRegion() = pkC0m4;
    pkC0m2->GetPortal(1)->AdjacentRegion() = pkC00;
    pkC20->GetPortal(0)->AdjacentRegion() = pkC40;
    pkC20->GetPortal(1)->AdjacentRegion() = pkC00;
    pkCm20->GetPortal(0)->AdjacentRegion() = pkC00;
    pkCm20->GetPortal(1)->AdjacentRegion() = pkCm40;
    pkC04->GetPortal(0)->AdjacentRegion() = pkDMP;
    pkC04->GetPortal(1)->AdjacentRegion() = pkDPP;
    pkC04->GetPortal(2)->AdjacentRegion() = pkC02;
    pkC0m4->GetPortal(0)->AdjacentRegion() = pkDPM;
    pkC0m4->GetPortal(1)->AdjacentRegion() = pkDMM;
    pkC0m4->GetPortal(2)->AdjacentRegion() = pkC0m2;
    pkC40->GetPortal(0)->AdjacentRegion() = pkDPP;
    pkC40->GetPortal(1)->AdjacentRegion() = pkDPM;
    pkC40->GetPortal(2)->AdjacentRegion() = pkC20;
    pkCm40->GetPortal(0)->AdjacentRegion() = pkDMM;
    pkCm40->GetPortal(1)->AdjacentRegion() = pkDMP;
    pkCm40->GetPortal(2)->AdjacentRegion() = pkCm20;
    pkDPP->GetPortal(0)->AdjacentRegion() = pkC40;
    pkDPP->GetPortal(1)->AdjacentRegion() = pkC04;
    pkDMP->GetPortal(0)->AdjacentRegion() = pkC04;
    pkDMP->GetPortal(1)->AdjacentRegion() = pkCm40;
    pkDMM->GetPortal(0)->AdjacentRegion() = pkCm40;
    pkDMM->GetPortal(1)->AdjacentRegion() = pkC0m4;
    pkDPM->GetPortal(0)->AdjacentRegion() = pkC0m4;
    pkDPM->GetPortal(1)->AdjacentRegion() = pkC40;

    // depth-first attachment
    pkC->AttachLeftChild(0);
    pkC->AttachRightChild(pkR);
        pkR->AttachLeftChild(0);
        pkR->AttachRightChild(pkRR);
            pkRR->AttachLeftChild(pkRRL);
                pkRRL->AttachLeftChild(pkRRLL);
                    pkRRLL->AttachLeftChild(pkRRLLL);
                        pkRRLLL->AttachLeftChild(0);
                        pkRRLLL->AttachRightChild(pkDPP);
                    pkRRLL->AttachRightChild(0);
                pkRRL->AttachRightChild(pkRRLR);
                    pkRRLR->AttachLeftChild(pkRRLRL);
                        pkRRLRL->AttachLeftChild(pkRRLRLL);
                            pkRRLRLL->AttachLeftChild(0);
                            pkRRLRLL->AttachRightChild(pkDPM);
                        pkRRLRL->AttachRightChild(0);
                    pkRRLR->AttachRightChild(pkRRLRR);
                        pkRRLRR->AttachLeftChild(pkRRLRRL);
                            pkRRLRRL->AttachLeftChild(0);
                            pkRRLRRL->AttachRightChild(pkC40);
                        pkRRLRR->AttachRightChild(pkC20);
            pkRR->AttachRightChild(pkRRR);
                pkRRR->AttachLeftChild(pkRRRL);
                    pkRRRL->AttachLeftChild(pkRRRLL);
                        pkRRRLL->AttachLeftChild(pkRRRLLL);
                            pkRRRLLL->AttachLeftChild(0);
                            pkRRRLLL->AttachRightChild(pkDMP);
                        pkRRRLL->AttachRightChild(0);
                    pkRRRL->AttachRightChild(pkRRRLR);
                        pkRRRLR->AttachLeftChild(pkRRRLRL);
                            pkRRRLRL->AttachLeftChild(pkRRRLRLL);
                                pkRRRLRLL->AttachLeftChild(0);
                                pkRRRLRLL->AttachRightChild(pkDMM);
                            pkRRRLRL->AttachRightChild(0);
                        pkRRRLR->AttachRightChild(pkRRRLRR);
                            pkRRRLRR->AttachLeftChild(pkRRRLRRL);
                                pkRRRLRRL->AttachLeftChild(0);
                                pkRRRLRRL->AttachRightChild(pkCm40);
                            pkRRRLRR->AttachRightChild(pkCm20);
                pkRRR->AttachRightChild(pkRRRR);
                    pkRRRR->AttachLeftChild(pkRRRRL);
                        pkRRRRL->AttachLeftChild(pkRRRRLL);
                            pkRRRRLL->AttachLeftChild(0);
                            pkRRRRLL->AttachRightChild(pkC04);
                        pkRRRRL->AttachRightChild(pkC02);
                    pkRRRR->AttachRightChild(pkRRRRR);
                        pkRRRRR->AttachLeftChild(pkRRRRRL);
                            pkRRRRRL->AttachLeftChild(pkRRRRRLL);
                                pkRRRRRLL->AttachLeftChild(0);
                                pkRRRRRLL->AttachRightChild(pkC0m4);
                            pkRRRRRL->AttachRightChild(pkC0m2);
                        pkRRRRR->AttachRightChild(pkC00);
    return pkC;
}
//----------------------------------------------------------------------------
bool Portals::InitializeTextures ()
{
    Texture* pkTexture;
    Image* pkImage;

    pkTexture = new Texture;
    pkImage = Image::Load("Agate.mif");
    if ( !pkImage ) return false;
    pkTexture->SetImage(pkImage);
    pkTexture->Filter() = Texture::FM_LINEAR;
    pkTexture->Mipmap() = Texture::MM_LINEAR;
    pkTexture->Wrap() = Texture::WM_CLAMP_S_CLAMP_T;
    m_spkTextureAgate = new TextureState;
    m_spkTextureAgate->Set(0,pkTexture);

    pkTexture = new Texture;
    pkImage = Image::Load("Bark.mif");
    if ( !pkImage ) return false;
    pkTexture->SetImage(pkImage);
    pkTexture->Filter() = Texture::FM_LINEAR;
    pkTexture->Mipmap() = Texture::MM_LINEAR;
    pkTexture->Wrap() = Texture::WM_CLAMP_S_CLAMP_T;
    m_spkTextureBark = new TextureState;
    m_spkTextureBark->Set(0,pkTexture);

    pkTexture = new Texture;
    pkImage = Image::Load("Buff.mif");
    if ( !pkImage ) return false;
    pkTexture->SetImage(pkImage);
    pkTexture->Filter() = Texture::FM_LINEAR;
    pkTexture->Mipmap() = Texture::MM_LINEAR;
    pkTexture->Wrap() = Texture::WM_CLAMP_S_CLAMP_T;
    m_spkTextureBuff = new TextureState;
    m_spkTextureBuff->Set(0,pkTexture);

    pkTexture = new Texture;
    pkImage = Image::Load("Connector.mif");
    if ( !pkImage ) return false;
    pkTexture->SetImage(pkImage);
    pkTexture->Filter() = Texture::FM_LINEAR;
    pkTexture->Mipmap() = Texture::MM_LINEAR;
    pkTexture->Wrap() = Texture::WM_CLAMP_S_CLAMP_T;
    m_spkTextureConnector = new TextureState;
    m_spkTextureConnector->Set(0,pkTexture);

    pkTexture = new Texture;
    pkImage = Image::Load("Dave.mif");
    if ( !pkImage ) return false;
    pkTexture->SetImage(pkImage);
    pkTexture->Filter() = Texture::FM_LINEAR;
    pkTexture->Mipmap() = Texture::MM_LINEAR;
    pkTexture->Wrap() = Texture::WM_CLAMP_S_CLAMP_T;
    m_spkTextureDave = new TextureState;
    m_spkTextureDave->Set(0,pkTexture);

    pkTexture = new Texture;
    pkImage = Image::Load("Munch.mif");
    if ( !pkImage ) return false;
    pkTexture->SetImage(pkImage);
    pkTexture->Filter() = Texture::FM_LINEAR;
    pkTexture->Mipmap() = Texture::MM_LINEAR;
    pkTexture->Wrap() = Texture::WM_CLAMP_S_CLAMP_T;
    m_spkTextureMunch = new TextureState;
    m_spkTextureMunch->Set(0,pkTexture);

    pkTexture = new Texture;
    pkImage = Image::Load("Pebbles.mif");
    if ( !pkImage ) return false;
    pkTexture->SetImage(pkImage);
    pkTexture->Filter() = Texture::FM_LINEAR;
    pkTexture->Mipmap() = Texture::MM_LINEAR;
    pkTexture->Wrap() = Texture::WM_CLAMP_S_CLAMP_T;
    m_spkTexturePebbles = new TextureState;
    m_spkTexturePebbles->Set(0,pkTexture);

    pkTexture = new Texture;
    pkImage = Image::Load("Quartz.mif");
    if ( !pkImage ) return false;
    pkTexture->SetImage(pkImage);
    pkTexture->Filter() = Texture::FM_LINEAR;
    pkTexture->Mipmap() = Texture::MM_LINEAR;
    pkTexture->Wrap() = Texture::WM_CLAMP_S_CLAMP_T;
    m_spkTextureQuartz = new TextureState;
    m_spkTextureQuartz->Set(0,pkTexture);

    pkTexture = new Texture;
    pkImage = Image::Load("Sand.mif");
    if ( !pkImage ) return false;
    pkTexture->SetImage(pkImage);
    pkTexture->Filter() = Texture::FM_LINEAR;
    pkTexture->Mipmap() = Texture::MM_LINEAR;
    pkTexture->Wrap() = Texture::WM_CLAMP_S_CLAMP_T;
    m_spkTextureSand = new TextureState;
    m_spkTextureSand->Set(0,pkTexture);

    pkTexture = new Texture;
    pkImage = Image::Load("Shelly.mif");
    if ( !pkImage ) return false;
    pkTexture->SetImage(pkImage);
    pkTexture->Filter() = Texture::FM_LINEAR;
    pkTexture->Mipmap() = Texture::MM_LINEAR;
    pkTexture->Wrap() = Texture::WM_CLAMP_S_CLAMP_T;
    m_spkTextureShelly = new TextureState;
    m_spkTextureShelly->Set(0,pkTexture);

    pkTexture = new Texture;
    pkImage = Image::Load("Sky.mif");
    if ( !pkImage ) return false;
    pkTexture->SetImage(pkImage);
    pkTexture->Filter() = Texture::FM_LINEAR;
    pkTexture->Mipmap() = Texture::MM_LINEAR;
    pkTexture->Wrap() = Texture::WM_CLAMP_S_CLAMP_T;
    m_spkTextureSky = new TextureState;
    m_spkTextureSky->Set(0,pkTexture);

    pkTexture = new Texture;
    pkImage = Image::Load("Water.mif");
    if ( !pkImage ) return false;
    pkTexture->SetImage(pkImage);
    pkTexture->Filter() = Texture::FM_LINEAR;
    pkTexture->Mipmap() = Texture::MM_LINEAR;
    pkTexture->Wrap() = Texture::WM_CLAMP_S_CLAMP_T;
    m_spkTextureWater = new TextureState;
    m_spkTextureWater->Set(0,pkTexture);

    return true;
}
//----------------------------------------------------------------------------
bool Portals::OnInitialize ()
{
    if ( !Application::OnInitialize() )
        return false;

    // set up camera
    ms_spkCamera->SetFrustum(0.1f,100.0f,-0.055f,0.055f,0.04125f,-0.04125f);
    Vector3f kCLoc(0.0f,0.0f,1.0f);
    Vector3f kCLeft(-1.0f,0.0f,0.0f);
    Vector3f kCUp(0.0f,0.0f,1.0f);
    Vector3f kCDir(0.0f,1.0f,0.0f);
    ms_spkCamera->SetFrame(kCLoc,kCLeft,kCUp,kCDir);

    // set up scene
    m_spkScene = new Node;

    m_spkWireframe = new WireframeState;
    m_spkWireframe->Enabled() = false;
    m_spkScene->SetRenderState(m_spkWireframe);

    m_spkZBuffer = new ZBufferState;
    m_spkZBuffer->Enabled() = true;
    m_spkZBuffer->Writeable() = true;
    m_spkZBuffer->Compare() = ZBufferState::CF_LEQUAL;
    m_spkScene->SetRenderState(m_spkZBuffer);

    if ( !InitializeTextures() )
        return true;

    ConvexRegionManager* pkCRM = CreateBspTree();
    pkCRM->AttachOutside(CreateOutside());
    m_spkScene->AttachChild(pkCRM);

    // initial update of objects
    ms_spkCamera->Update();
    m_spkScene->UpdateGS(0.0f);
    m_spkScene->UpdateRS();

    m_bTurretActive = true;
    SetTurretAxes();
    m_fTrnSpeed = 0.01f;
    m_fRotSpeed = 0.01f;

    m_bInitialized = true;
    return true;
}
//----------------------------------------------------------------------------
void Portals::OnTerminate ()
{
    m_spkZBuffer = NULL;
    m_spkWireframe = NULL;
    m_spkTextureAgate = NULL;
    m_spkTextureBark = NULL;
    m_spkTextureBuff = NULL;
    m_spkTextureConnector = NULL;
    m_spkTextureDave = NULL;
    m_spkTextureMunch = NULL;
    m_spkTexturePebbles = NULL;
    m_spkTextureQuartz = NULL;
    m_spkTextureSand = NULL;
    m_spkTextureShelly = NULL;
    m_spkTextureSky = NULL;
    m_spkTextureWater = NULL;
    m_spkScene = NULL;

    Application::OnTerminate();
}
//----------------------------------------------------------------------------
void Portals::OnIdle ()
{
    MeasureTime();

    MoveCamera();

    ms_spkRenderer->ClearBuffers();
    if ( ms_spkRenderer->BeginScene() )
    {
        if ( m_bInitialized )
        {
            ms_spkRenderer->Draw(m_spkScene);
            DrawFrameRate(8,GetHeight()-8,ColorRGB::WHITE);
        }
        else
        {
            ms_spkRenderer->Draw(8,16,ColorRGB::WHITE,
                "Load of texture images failed.");
            ms_spkRenderer->Draw(8,32,ColorRGB::WHITE,
                "Make sure these files are in the same directory as the "
                "executable.");
        }

        ms_spkRenderer->EndScene();
    }
    ms_spkRenderer->DisplayBackBuffer();

    UpdateClicks();
}
//----------------------------------------------------------------------------
void Portals::OnKeyDown (unsigned char ucKey, int, int)
{
    if ( ucKey == 'q' || ucKey == 'Q' || ucKey == KEY_ESCAPE )
    {
        RequestTermination();
        return;
    }

    switch ( ucKey )
    {
    case '0':  // reset frame rate measurements
        ResetTime();
        return;
    case 'w':
        m_spkWireframe->Enabled() = !m_spkWireframe->Enabled();
        return;
    }
}
//----------------------------------------------------------------------------
