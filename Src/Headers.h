#ifndef HEADERS_H
#define HEADERS_H

#include "Global.h"
#include "Math.h"
#include "Geometry.h"
#include "Statistics.h"

#include <GL/glew.h>

#include <QFileInfoList>
#include <QMessageBox>
#include <QGLWidget>
#include <QKeyEvent>
#include <QDebug>
#include <QTimer>
#include <QColor>
#include <QDate>
#include <QTime>
#include <QDir>

#include <GL/freeglut.h>

class Shader;
class Light;

using namespace std;

#undef min
#undef max

extern Statistics stats;

struct Transform
{
    mat4 view;
    mat4 projection;
    mat3 normal;
    mat4 viewProjection;
    mat4 modelViewProjection;
    vector<mat4> lightViews;
};

struct GlobalObjectParams
{
    vec3 camPos;
    vec2 blur;
    vec2 windowSize;
    vec4 clipPlaneGround;

    int   gridRenderMode;
    int   polygonMode;

    bool  applyShadow;
    bool  renderMesh;
    bool  renderObjects;
    bool  renderTextures;
    bool  renderWireframe;
    bool  renderNormals;
    bool  renderMisc;
	bool  renderTarget;
	bool  renderCurrent;
	bool  renderPointCloud;
    bool  renderGenerations;
    bool  isPartial;
    bool  renderBoxes;
    bool  renderConnectors;
    float boxTransparency;

    vec2 shadowMapSize;

    float shadowIntensity;
    float depthRangeMax;
    float depthRangeMin;
    float polygonOffsetFactor;
    float polygonOffsetUnits;
    float ncp;
    float fcp;
    float fov;
    float sampleShading;
    float lightIntensity;
    float renderHeightOffset;

    vector<Light *> lights;
    int activeLight;

    int nrVertices;
    int nrActiveVertices;

	float weightProjection;
	float weightBoundingBox;
	float weightNegative;
	float weightDistanceField;
	float weightGrammar;
	float weightDisentangle;
    float weightSkin;

	int optIterations;
    int optParticles;
	float optScale;
	float optProbability;
    float optMean;
    float optStd;
    float optW;
    float optphip;
    float optphig;
    float optCrossover;
    float optMutation;
    int optBits;
    int optPopulation;

	double error;

    int optStrategy;
    int optTechnique;
};

struct Shaders
{
#ifdef WIN32
    Shader *default;
#else
    Shader *default_;
#endif
    Shader *defaultDepth;
    Shader *defaultLight;
    Shader *blur;
    Shader *grid;
    Shader *object;
    Shader *objectDepth;
    Shader *objectLines;
    Shader *gui;
    Shader *noise;
    Shader *tessellation;
    Shader *cookTorrance;
    Shader *sphericalHarmonic;
    Shader *box;
    Shader *scan;
    Shader *points;
};

typedef Singleton<GlobalObjectParams> params;
typedef Singleton<Shaders> shaders;




void glEnable2D(void);
void glDisable2D(void);
void glEnableFixedFunction(const Transform &trans);
void glDisableFixedFunction();

float cosineInterpolation(float a, double b, double s);
double hermiteInterpolation(double y0, double y1, double y2, double y3, double mu, double tension, double bias);

void renderTexture(uint texture, uint posX, uint posY, float width, float height);
void renderQuad(float size, float r, float g, float b, float a);
void renderQuad(float width, float height, float r, float g, float b, float a);
void renderQuad(float posX, float posY, float width, float height);
void renderOrigin(float lineWidth);
void screenSizeQuad(float width, float height, float fov);

#ifdef WIN32
void renderString(const char *str, int x, int y, vec4 &color, void *font = GLUT_BITMAP_HELVETICA_18);
#else
void renderString(const char *str, int x, int y, const vec4 &color, void *font = GLUT_BITMAP_HELVETICA_18);
#endif
void renderString(const char *str, int x, int y, float r, float g, float b, float a, void *font = GLUT_BITMAP_HELVETICA_18);

void smoothBackground(vec4 top, vec4 bottom, float windowWidth, float windowHeight);

void saveFrameBuffer(QGLWidget *widget);
void saveFrameBuffer(QGLWidget *widget, int idx);
void saveFrameBuffer(QGLWidget *widget, QString name);

void getCameraFrame(const Transform &trans, vec3 &dir, vec3 &up, vec3 &right, vec3 &pos);
vec3 getCamPosFromModelView(const Transform &trans);
vec3 getViewDirFromModelView(const Transform &trans);
vec3 getUpDirFromModelView(const Transform &trans);

void checkGLError();
void checkGLVersion();

static float colorJet[] = { 0.000000f, 0.000000f, 0.562500f, 0.000000f, 0.000000f, 0.625000f, 0.000000f, 0.000000f, 0.687500f, 0.000000f, 0.000000f, 0.750000f, 0.000000f, 0.000000f, 0.812500f, 0.000000f, 0.000000f, 0.875000f, 0.000000f, 0.000000f, 0.937500f, 0.000000f, 0.000000f, 1.000000f, 0.000000f, 0.062500f, 1.000000f, 0.000000f, 0.125000f, 1.000000f, 0.000000f, 0.187500f, 1.000000f, 0.000000f, 0.250000f, 1.000000f, 0.000000f, 0.312500f, 1.000000f, 0.000000f, 0.375000f, 1.000000f, 0.000000f, 0.437500f, 1.000000f, 0.000000f, 0.500000f, 1.000000f, 0.000000f, 0.562500f, 1.000000f, 0.000000f, 0.625000f, 1.000000f, 0.000000f, 0.687500f, 1.000000f, 0.000000f, 0.750000f, 1.000000f, 0.000000f, 0.812500f, 1.000000f, 0.000000f, 0.875000f, 1.000000f, 0.000000f, 0.937500f, 1.000000f, 0.000000f, 1.000000f, 1.000000f, 0.062500f, 1.000000f, 0.937500f, 0.125000f, 1.000000f, 0.875000f, 0.187500f, 1.000000f, 0.812500f, 0.250000f, 1.000000f, 0.750000f, 0.312500f, 1.000000f, 0.687500f, 0.375000f, 1.000000f, 0.625000f, 0.437500f, 1.000000f, 0.562500f, 0.500000f, 1.000000f, 0.500000f, 0.562500f, 1.000000f, 0.437500f, 0.625000f, 1.000000f, 0.375000f, 0.687500f, 1.000000f, 0.312500f, 0.750000f, 1.000000f, 0.250000f, 0.812500f, 1.000000f, 0.187500f, 0.875000f, 1.000000f, 0.125000f, 0.937500f, 1.000000f, 0.062500f, 1.000000f, 1.000000f, 0.000000f, 1.000000f, 0.937500f, 0.000000f, 1.000000f, 0.875000f, 0.000000f, 1.000000f, 0.812500f, 0.000000f, 1.000000f, 0.750000f, 0.000000f, 1.000000f, 0.687500f, 0.000000f, 1.000000f, 0.625000f, 0.000000f, 1.000000f, 0.562500f, 0.000000f, 1.000000f, 0.500000f, 0.000000f, 1.000000f, 0.437500f, 0.000000f, 1.000000f, 0.375000f, 0.000000f, 1.000000f, 0.312500f, 0.000000f, 1.000000f, 0.250000f, 0.000000f, 1.000000f, 0.187500f, 0.000000f, 1.000000f, 0.125000f, 0.000000f, 1.000000f, 0.062500f, 0.000000f, 1.000000f, 0.000000f, 0.000000f, 0.937500f, 0.000000f, 0.000000f, 0.875000f, 0.000000f, 0.000000f, 0.812500f, 0.000000f, 0.000000f, 0.750000f, 0.000000f, 0.000000f, 0.687500f, 0.000000f, 0.000000f, 0.625000f, 0.000000f, 0.000000f, 0.562500f, 0.000000f, 0.000000f, 0.500000f, 0.000000f, 0.000000f };
static float colorHot[] = { 0.041667f, 0.000000f, 0.000000f, 0.083333f, 0.000000f, 0.000000f, 0.125000f, 0.000000f, 0.000000f, 0.166667f, 0.000000f, 0.000000f, 0.208333f, 0.000000f, 0.000000f, 0.250000f, 0.000000f, 0.000000f, 0.291667f, 0.000000f, 0.000000f, 0.333333f, 0.000000f, 0.000000f, 0.375000f, 0.000000f, 0.000000f, 0.416667f, 0.000000f, 0.000000f, 0.458333f, 0.000000f, 0.000000f, 0.500000f, 0.000000f, 0.000000f, 0.541667f, 0.000000f, 0.000000f, 0.583333f, 0.000000f, 0.000000f, 0.625000f, 0.000000f, 0.000000f, 0.666667f, 0.000000f, 0.000000f, 0.708333f, 0.000000f, 0.000000f, 0.750000f, 0.000000f, 0.000000f, 0.791667f, 0.000000f, 0.000000f, 0.833333f, 0.000000f, 0.000000f, 0.875000f, 0.000000f, 0.000000f, 0.916667f, 0.000000f, 0.000000f, 0.958333f, 0.000000f, 0.000000f, 1.000000f, 0.000000f, 0.000000f, 1.000000f, 0.041667f, 0.000000f, 1.000000f, 0.083333f, 0.000000f, 1.000000f, 0.125000f, 0.000000f, 1.000000f, 0.166667f, 0.000000f, 1.000000f, 0.208333f, 0.000000f, 1.000000f, 0.250000f, 0.000000f, 1.000000f, 0.291667f, 0.000000f, 1.000000f, 0.333333f, 0.000000f, 1.000000f, 0.375000f, 0.000000f, 1.000000f, 0.416667f, 0.000000f, 1.000000f, 0.458333f, 0.000000f, 1.000000f, 0.500000f, 0.000000f, 1.000000f, 0.541667f, 0.000000f, 1.000000f, 0.583333f, 0.000000f, 1.000000f, 0.625000f, 0.000000f, 1.000000f, 0.666667f, 0.000000f, 1.000000f, 0.708333f, 0.000000f, 1.000000f, 0.750000f, 0.000000f, 1.000000f, 0.791667f, 0.000000f, 1.000000f, 0.833333f, 0.000000f, 1.000000f, 0.875000f, 0.000000f, 1.000000f, 0.916667f, 0.000000f, 1.000000f, 0.958333f, 0.000000f, 1.000000f, 1.000000f, 0.000000f, 1.000000f, 1.000000f, 0.062500f, 1.000000f, 1.000000f, 0.125000f, 1.000000f, 1.000000f, 0.187500f, 1.000000f, 1.000000f, 0.250000f, 1.000000f, 1.000000f, 0.312500f, 1.000000f, 1.000000f, 0.375000f, 1.000000f, 1.000000f, 0.437500f, 1.000000f, 1.000000f, 0.500000f, 1.000000f, 1.000000f, 0.562500f, 1.000000f, 1.000000f, 0.625000f, 1.000000f, 1.000000f, 0.687500f, 1.000000f, 1.000000f, 0.750000f, 1.000000f, 1.000000f, 0.812500f, 1.000000f, 1.000000f, 0.875000f, 1.000000f, 1.000000f, 0.937500f, 1.000000f, 1.000000f, 1.000000f };

void colorMap(float x, float * out, float * cm);
void colorMapBgr(float x, float * out, float * cm);

vec3 toTopOffset(const vec3 &size, float mod = 0.5f);
vec3 toBottomOffset(const vec3 &size, float mod = 0.5f);
vec3 toFrontOffset(const vec3 &size, float mod = 0.5f);
vec3 toBackOffset(const vec3 &size, float mod = 0.5f);
vec3 toLeftOffset(const vec3 &size, float mod = 0.5f);
vec3 toRightOffset(const vec3 &size, float mod = 0.5f);

#ifndef WIN32
double GetTickCount(void);
#endif

#endif
