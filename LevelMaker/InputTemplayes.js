let componentParent = document.getElementById("ComponentParent");

function forceNumber(Input){
 
    if(isNaN(Number(Input))){
        return 0;
    }
 
    return Number(Input);
}


let vec3 = function(component, title){
    this.element = document.createElement("div");
    component.appendChild(this.element);

    this.element.outerHTML = "<li id='Finder'><div id='text'>" + title + "</div></div><ul id='Inputs'><li> X </li><li><input id='FinderX'></li><li> Y </li><li><input id='FinderY'></li><li> Z </li><li><input id='FinderZ'></li></ul></li>"
    this.element = document.getElementById("Finder");
    this.element.id = "vec3";

    this.xElement = document.getElementById("FinderX");
    this.xElement.id = "";
    
    this.getX = function(){
        return forceNumber(this.xElement.value);
    }

    this.yElement = document.getElementById("FinderY");
    this.yElement.id = "";
    
    this.getY = function(){
        return forceNumber(this.yElement.value);
    }

    this.zElement = document.getElementById("FinderZ");
    this.zElement.id = "";
    
    this.getZ = function(){
        return forceNumber(this.zElement.value);
    }

    this.toString = function(){
        return this.getX() + "," + this.getY() + "," + this.getZ();
    }
}

let Component = function(title){
    this.element = document.createElement("div");
    componentParent.appendChild(this.element);
    this.element.outerHTML = "<div id='Finder'><div id='title'>" + title + "</div><ul id='FindParamParent'></ul></div>";
    this.element = document.getElementById("Finder");
    this.element.id = "Component";
    this.paramParent = document.getElementById("FindParamParent")
    this.paramParent.id = "paramParent";

    this.addVec3 = function(title){
        return new vec3(this.paramParent,title);
    }
}

let Transform = function(){
    let comp = new Component("Transform");
    let position = comp.addVec3("Position");
    let Rotation = comp.addVec3("Rotation");
    let Scale = comp.addVec3("Scale");

    this.toString = function(){
        let data = "";
        data += "Translate(" + position.toString() + "-";
        data += "Rotate(" + Rotation.toString() + "-";
        data += "Scale(" + Scale.toString();
        return data;
    }
}