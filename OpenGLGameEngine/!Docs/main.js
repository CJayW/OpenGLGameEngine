function makeElement(type,parent = document.body){
    let el = document.createElement(type);
    parent.appendChild(el);
    return el;
}

let components = JSON.parse('[{"Title":"Transform","Description":"Used for Rendering the Scene.\\nIts GameObjects Transform is used for the exact position and rotation to Render from.","Constructor":["void Camera()"],"functions":[{"Title":"Get Model Matrix","Description":"Get the model matrix relative to the world","Example":"glm::mat4 GetModelMat();"},{"Title":"Get Position","Description":"gets the position of the object relative to world space","Example":"glm::vec3 getPosition();"},{"Title":"Get Rotation","Description":"gets the rotation of the object relative to world space","Example":"glm::quat getRotation();"}],"variables":[{"Name":"glm::vec3 localPos","Description":"The positon of the object relative to its axis"},{"Name":"glm::vec3 rotation","Description":"The Rotation of the object relative to its axis"},{"Name":"glm::vec3 scale","Description":"The Scale of the object relative to its axis"}]},{"Title":"Camera","Description":"Used for Rendering the Scene.\\nIts GameObjects Transform is used for the exact position and rotation to Render from.","Constructor":["void Camera()"],"functions":[{"Title":"Update Camera View","Description":"Updates the view matrix for all stored Renderers.","Example":"void UpdateCameraView()"},{"Title":"Update Camera Projection","Description":"Updates the view matrix for all stored Renderers.","Example":"static void UpdateCameraProjection()"}],"variables":[{"Name":"static float FOV","Description":"The Field of view that everything is Renderer with."},{"Name":"static glm::mat4 projection","Description":"The Projection matrix that is used for Rendering"},{"Name":"static glm::mat4 viewMatrix","Description":"The View matrix that is used for Rendering"}]},{"Title":"Mesh Renderer","Description":"Used to render a 3D models","Constructor":["void MeshRenderer()","void MeshRenderer(std::string modelName)"],"functions":[{"Title":"Update Camera Projection","Description":"Called from Camera.\\nUpdates the camer projection in the shader program","Example":"void UpdateCameraProjection() override"},{"Title":"Load Model","Description":"Uses the ModelLocation to load the mesh","Example":"void loadModel()"}],"variables":[{"Description":"The Shader Program that is used for all MeshRenderers"},{"Name":"std::string ModelLocation","Description":"The exact file location that the model is stored at"},{"Name":"std::string loadName","Description":"The file name that the model is loaded from"},{"Name":"bool modelLoaded","Description":"whether the model has been loaded and is being displayed"}]},{"Title":"Icon Renderer","Description":"Used to render icons while in editor mode","Constructor":["void IconRenderer()","void IconRenderer(std::string iconName)"],"functions":[{"Title":"load Icon","Description":"Called from Camera.\\nUpdates the camer projection in the shader program","Example":"void loadIcon();"},{"Title":"Update Camera Projection","Description":"Takes uses the iconLocation to load the icon","Example":"void UpdateCameraProjection() override"}],"variables":[{"Name":"std::string iconLocation","Description":"The location that the icon is loaded from"},{"Name":"std::string loadName","Description":"The name of the file that the icon is loaded from"},{"Name":"bool iconLoaded","Description":"Whether the icon has been loaded or not"}]},{"Title":"RigidBody","Description":"IN DEVELOPMENT\\nused to apply simply physics to shapes\\n- Currently, There is no rotation, the object has gravity applied to it until it hits the floor","Constructor":["void IconRenderer()","void IconRenderer(std::string params)"],"functions":[{"Title":"Add Force","Description":"Adds force to the component based off its mass","Example":"void addForce(glm::vec3 force);"}],"variables":[{"Name":"float mass","Description":"The Mass of the Object"},{"Name":"float drag","Description":"The Drag Applied to the object per frame"},{"Name":"glm::vec3 gravity","Description":"The Gravity Applied to the object per frame"},{"Name":"glm::vec3 velocity","Description":"The Current Velocity of the Object"}]},{"Title":"SpotLight","Description":"A light caster that creates a cone of light with a drop-off","Constructor":["void Spotlight()","void SpotLight(std::string params)"],"functions":[{"Title":"Update Light","Description":"tells the shader program to update the light","Example":"void UpdateLight() override;"}],"variables":[{"Name":"glm::vec3 diffuse","Description":"the diffuse colour of the light"},{"Name":"float constant","Description":"The Constant drop-off of the light"},{"Name":"float  linear","Description":"The linear drop-off of the light"},{"Name":"float quadratic","Description":"The quadratic drop-off of the light"},{"Name":"float width","Description":"The width of the cone that is created"},{"Name":"float blur","Description":"the blur of the cone, as a decimal"}]},{"Title":"Point light","Description":"A light caster that creates a light with drop off, the direction is does not affect anything","Constructor":["void PointLight()","void PointLight(std::string params)"],"functions":[{"Title":"Update Light","Description":"tells the shader program to update the light","Example":"void UpdateLight() override;"}],"variables":[{"Name":"glm::vec3 diffuse","Description":"the diffuse colour of the light"},{"Name":"float constant","Description":"The Constant drop-off of the light"},{"Name":"float  linear","Description":"The linear drop-off of the light"},{"Name":"float quadratic","Description":"The quadratic drop-off of the light"}]},{"Title":"Directional Light","Description":"A light caster with a constant direction and no drop-off","Constructor":["void DirectionalLight()","void DirectionalLight(std::string params)"],"functions":[{"Title":"Update Light","Description":"tells the shader program to update the light","Example":"void UpdateLight() override;"}],"variables":[{"Name":"glm::vec3 diffuse","Description":"the diffuse colour of the light"}]}]')

let elements = document.getElementById("Elements");

let sideUL = document.getElementById("sideUL");

components.forEach((compInfo)=>{
    //sidbar link
    let target = makeElement("a", elements);
    target.name = compInfo.Title;

    let li = makeElement("li", sideUL);
    let a = makeElement("a", li);
    
    a.setAttribute('href','#' + compInfo.Title);

    a.innerText = compInfo.Title;


    let el = makeElement("div", elements);
    el.className = "Element";

    let title = makeElement("h3", el);
    title.innerText = compInfo.Title;
    title.style.margin = "0";

    let Description = makeElement("p", el);
    Description.innerText = compInfo.Description;

    makeElement("h4", el).innerText = "Constructor:";

    compInfo.Constructor.forEach((constructor)=>{
        let con = makeElement("code", el);
        con.innerText = constructor;
        makeElement("p", el).style.margin = "10px";
    })

    let funcTitle = makeElement("h4", el);
    funcTitle.innerText = "Function:";

    let funcs = makeElement("ul", el);

    compInfo.functions.forEach(funcInfo => {
        let func = makeElement("li", funcs);
        
        let func1 = makeElement("h4", func);
        func1.innerText = funcInfo.Title;
        
        let Func1Description = makeElement("p",func);
        Func1Description.innerText = funcInfo.Description;
        
        let code = makeElement("code", func);
        code.innerText = funcInfo.Example;
    });

    makeElement("h4", el).innerText = "Variables";

    let vars = makeElement("ul", el);

    compInfo.variables.forEach((varInfo)=>{
        let varHolder = makeElement("li", vars);
        
        makeElement("code", varHolder).innerText = varInfo.Name;
        
        makeElement("p",varHolder).innerText = varInfo.Description;

    });
});