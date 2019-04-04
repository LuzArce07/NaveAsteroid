#include "stdafx.h"
#include "Nave.h"

Nave::Nave() {

	angulo = 0.0f;
	coordenadas = vec3(0.0f, 0.0f, 0.0f);

	//Establece el valor como una matriz identidad
	transformaciones = mat4(1.0f);

}

void Nave::rotar(Direccion direccion) {

	float rotacion = velocidadAngular;
	if(direccion == Direccion::Derecha){

		rotacion = -rotacion;
	
	}
	angulo += rotacion;

}

void Nave::avanzar() {

	vec3 traslacion = vec3(
		cos(angulo * 3.14159 / 180.0f) * velocidad, //x
		sin(angulo * 3.14159 / 180.0f) * velocidad, //y
		0.0f //z
	);

	coordenadas += traslacion;
	actualizarMatrizTransformacion();

}

void Nave::actualizarMatrizTransformacion() {
	
	//Partir siempre de una matriz identidad
	transformaciones = mat4(1.0f);
	//Aplicar las transformaciones
	transformaciones = translate(transformaciones, coordenadas);
	transformaciones = rotate(transformaciones, (angulo * 3.14159f / 180.0f), vec3(0.0f, 0.0f, 1.0f));

}