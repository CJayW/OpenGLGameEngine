//* represents that each parameter needs a different title
let componentTypes = [
    "Transform* Translate(vec3:Rotate(vec3:Scale(vec3",
    "Camera FOV(float",
    "MeshRenderer ",
    "CameraMovement moveSpeed(float:lookSpeed(float",
    "TestMove moveSpeed(float:rotateSpeed(float:rotateSpeedM(float"
]

let Component = function(componentTypeIndex){
    this.type = componentTypeIndex;

    let title = componentTypes[componentTypeIndex].split(" ")[0];

    let addComponentName = true;

    if(title[title.length - 1] == '*'){
        title = title.split('*')[0];
        addComponentName = false;
    }

    this.element = document.createElement("div");
    componentParent.appendChild(this.element);
    this.element.outerHTML = "<div id='Finder'><div id='title'>" + title + "</div><ul id='FindParamParent'></ul></div>";
    this.element = document.getElementById("Finder");
    this.element.id = "Component";
    this.paramParent = document.getElementById("FindParamParent")
    this.paramParent.id = "paramParent";

    this.params = [];

    this.addVec3 = function(title){
        this.params.push(new vec3(this.paramParent,title));
    }

    this.addFloat = function(title){
        this.params.push(new float(this.paramParent,title));
    }

    let sComponentParams = componentTypes[componentTypeIndex].split(" ")[1];
    componentParams = sComponentParams.split(':');

    componentParams.forEach(element => {
        let param = element.split("(");
        switch (param[1]) {
            case "float":
                this.addFloat(param[0]);
                break;

            case "vec3":
                this.addVec3(param[0]);
                break;

            default:
                console.log("No Param Added with this name: " + param[1]);
                break;
        }
    });

    this.toString = function(){
        let data = "";

        if(addComponentName){
            data += title + "(";
        }

        for(let i = 0; i < this.params.length; i++){
            data += this.params[i].toString(!addComponentName);
            if(i != this.params.length -1){
                data += ",";
            }
        }
        return data;
    }
}