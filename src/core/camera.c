 
Camera CAMERA_START(Camera *camera)
{
	camera->position = ( Vector3 ){10.0f, 10.0f, 10.0f};
	camera->target = ( Vector3 ){0.0f, 0.0f, 0.0f};
	camera->up = ( Vector3 ){0.0f, 1.0f, 0.0f};
	camera->fovy = 30.0f;
	camera->projection = CAMERA_PERSPECTIVE;
	SetCameraMode ( *camera, CAMERA_FREE );
	return (*camera);
}
