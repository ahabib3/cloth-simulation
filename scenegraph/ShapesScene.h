#ifndef SHAPESSCENE_H
#define SHAPESSCENE_H

#include "OpenGLScene.h"

#include <memory>

#include <GL/glew.h>

#include "gl/datatype/FBO.h"
#include "Settings.h"
#include "shapes/Sheet.h"
#include "shapes/Sphere.h"

#include "gl/textures/Texture2D.h"
#include "gl/textures/Texture.h"

#include <unordered_map>


namespace CS123 { namespace GL {

    class Shader;
    class CS123Shader;
    class FullScreenQuad;

}}

class Shape;

/**
 *
 * @class ShapesScene
 *
 * A scene that is used to render a single shape.
 *
 * This scene has no notion of the scene graph, so it will not be useful to you in
 * assignments requiring the display of multiple shapes. Luckily, the first time you
 * will need that kind of functionality is in the Sceneview assignment... and we've
 * left that task up to you in the SceneviewScene class.
 *
 * By default, the ShapesScene displays only a single triangle. You'll need to do
 * a little work here to render your shapes. You could render the shapes directly
 * in this class, or you could pass the work on to one or more subclasses. Think
 * carefully about your design here - you'll be reusing your shapes multiple times
 * during this course!
 */
class ShapesScene : public OpenGLScene {
public:
    ShapesScene(int width, int height);
    virtual ~ShapesScene();

    virtual void render(SupportCanvas3D *context) override;
    virtual void settingsChanged() override;


protected:
    // Set the light uniforms for the lights in the scene. (The view matrix is used so that the
    // light can follows the camera.)
    virtual void setLights(const glm::mat4 viewMatrix);

    // Render geometry for Shapes and Sceneview.
    virtual void renderGeometry();

    virtual void updateCloth();

private:
    // Storage for private copies of the scene's light and material data. Note that these don't
    // need to be freed because they are VALUE types (not pointers) and the memory for them is
    // freed when the class itself is freed.
    std::unique_ptr<CS123::GL::CS123Shader> m_phongShader;
    std::unique_ptr<CS123::GL::Shader> m_wireframeShader;
    std::unique_ptr<CS123::GL::Shader> m_normalsShader;
    std::unique_ptr<CS123::GL::Shader> m_normalsArrowShader;
    std::unique_ptr<CS123::GL::Shader> m_fsqShader;
    CS123SceneLightData  m_light;
    CS123SceneLightData m_light2;
    CS123SceneMaterial   m_material;
    CS123SceneMaterial   m_materialSphere;

    glm::vec4 m_lightDirection = glm::normalize(glm::vec4(0.5f, -1.f, -1.f, 0.f));
    glm::vec4 m_lightDirection2 = glm::normalize(glm::vec4(-0.5f, 1.f, -0.5f, 0.f));

    // essentially an OpenGLShape from lab 1
    std::unique_ptr<Shape> m_square;
    std::unique_ptr<Sheet> m_sheet;
    std::unique_ptr<Sphere> m_sphere;

    std::unordered_map<int, CS123::GL::Texture2D> m_textureMap;

    int m_width;
    int m_height;

    void clearLights();
    void loadPhongShader();
    void loadWireframeShader();
    void loadNormalsShader();
    void loadNormalsArrowShader();
    void renderPhongPass(SupportCanvas3D *context);
    void renderGeometryAsFilledPolygons();
    void renderWireframePass(SupportCanvas3D *context);
    void renderGeometryAsWireframe();
    void renderNormalsPass(SupportCanvas3D *context);
    void initializeSceneMaterial();
    void initializeSceneLight();
    void setPhongSceneUniforms(const CS123SceneMaterial &m);
    void setMatrixUniforms(CS123::GL::Shader *shader, SupportCanvas3D *context);
    void renderFilledPolygons();
    void renderNormals();
    void renderWireframe();
    void setSceneUniforms(SupportCanvas3D *context);

    void loadTextures(const std::string &filePath, const int num);
    void enableTexture();

};

#endif // SHAPESSCENE_H
