void TECLADO_MAIN(MQDATA *data)
{
    if(IsKeyPressed(KEY_ESCAPE))
    {
        MQEXIT = MQMenu(*&data, 1);
    }
    if(IsKeyPressed(KEY_E) || IsKeyPressed(KEY_E))
    {
        MQPlayerPickupItem(*&data,0);
    } 
    if(IsKeyDown(KEY_RIGHT) || IsKeyDown(KEY_D))
    {
        if(data->game.player[0].rotation == 0)
            data->game.player[0].rotation = 360;
        data->game.player[0].rotation -= 6;
    }
    if(IsKeyDown(KEY_LEFT) || IsKeyDown(KEY_A))
    {
        if(data->game.player[0].rotation == 360)
            data->game.player[0].rotation = 0;
        data->game.player[0].rotation += 6;
    }
    if(IsKeyPressed(KEY_DOWN) || IsKeyPressed(KEY_S))
    {
        data->session.render.model[MQFindRenderModel(*data,"player0")].reverse = true;
        data->session.render.model[MQFindRenderModel(*data,"player0")].currentAnim = 1;
    }
    if(IsKeyDown(KEY_DOWN) || IsKeyDown(KEY_S))
    {

        data->game.player[0].position = MQPlayerMove(data->game.player[0].position, data->game.player[0].rotation, (data->game.player[0].speed) * (-1));
        float reverseRotation;
        if(data->game.player[0].rotation<180)
            reverseRotation = 180 + data->game.player[0].rotation;
        else
            reverseRotation = data->game.player[0].rotation-180;
        
        Vector3 Vec3buff = MQCheckWall(*data,"player-barriga0",reverseRotation,data->game.other.wallexclude[MQFindWallexclude(*data,"playerwallexclude0")]);
        if(Vec3buff.x != __INT_MAX__)
        {
            if(data->game.player[0].position.x+0.5 > Vec3buff.x&&data->game.player[0].position.x-0.5<Vec3buff.x)
                data->game.player[0].position.x = Vec3buff.x;
        } 
        if(Vec3buff.z != __INT_MAX__)
        {
            if(data->game.player[0].position.z+0.5 > Vec3buff.z&&data->game.player[0].position.z-0.5<Vec3buff.z)
                data->game.player[0].position.z = Vec3buff.z;
        }


        if(data->game.other.wallexclude[MQFindWallexclude(*data,"playerwallexclude0")].index != __INT_MAX__)
        {
            data->game.other.wallexclude[MQFindWallexclude(*data,"playerwallexclude0")].exclude=true;
            Vec3buff = MQCheckWall(*data,"player-barriga0",reverseRotation,data->game.other.wallexclude[MQFindWallexclude(*data,"playerwallexclude0")]);
            if(Vec3buff.x != __INT_MAX__)
            {
                if(data->game.player[0].position.x+0.5 > Vec3buff.x&&data->game.player[0].position.x-0.5<Vec3buff.x)
                    data->game.player[0].position.x = Vec3buff.x;
            } 
            if(Vec3buff.z != __INT_MAX__)
            {
                if(data->game.player[0].position.z+0.5 > Vec3buff.z&&data->game.player[0].position.z-0.5<Vec3buff.z)
                    data->game.player[0].position.z = Vec3buff.z;
            }
        }
    }
    if(IsKeyPressed(KEY_UP) || IsKeyPressed(KEY_W))
    {
        data->session.render.model[MQFindRenderModel(*data,"player0")].currentAnim = 1;
    }
    if(IsKeyDown(KEY_UP) || IsKeyDown(KEY_W))
    {
        data->game.player[0].position = MQPlayerMove(data->game.player[0].position, data->game.player[0].rotation, data->game.player[0].speed);
        Vector3 Vec3buff = MQCheckWall(*data,"player-barriga0",data->game.player[0].rotation,data->game.other.wallexclude[MQFindWallexclude(*data,"playerwallexclude0")]);
        if(Vec3buff.x != __INT_MAX__)
        {
            if(data->game.player[0].position.x+0.5 > Vec3buff.x&&data->game.player[0].position.x-0.5<Vec3buff.x)
                data->game.player[0].position.x = Vec3buff.x;
        } 
        if(Vec3buff.z != __INT_MAX__)
        {
            if(data->game.player[0].position.z+0.5 > Vec3buff.z&&data->game.player[0].position.z-0.5<Vec3buff.z)
                data->game.player[0].position.z = Vec3buff.z;
        }


        if(data->game.other.wallexclude[MQFindWallexclude(*data,"playerwallexclude0")].index != __INT_MAX__)
        {
            data->game.other.wallexclude[MQFindWallexclude(*data,"playerwallexclude0")].exclude=true;
            Vec3buff = MQCheckWall(*data,"player-barriga0",data->game.player[0].rotation,data->game.other.wallexclude[MQFindWallexclude(*data,"playerwallexclude0")]);
            if(Vec3buff.x != __INT_MAX__)
            {
                if(data->game.player[0].position.x+0.5 > Vec3buff.x&&data->game.player[0].position.x-0.5<Vec3buff.x)
                    data->game.player[0].position.x = Vec3buff.x;
            } 
            if(Vec3buff.z != __INT_MAX__)
            {
                if(data->game.player[0].position.z+0.5 > Vec3buff.z&&data->game.player[0].position.z-0.5<Vec3buff.z)
                    data->game.player[0].position.z = Vec3buff.z;
            }
        }
    }
    if(IsKeyDown(KEY_LEFT_SHIFT))
    {
        data->game.player[0].speed = 0.2f;
    }
    if(IsKeyReleased(KEY_LEFT_SHIFT))
    {
        data->game.player[0].speed = 0.1f;
    }
    if(IsKeyReleased(KEY_UP) || IsKeyReleased(KEY_W))
    {
        data->session.render.model[MQFindRenderModel(*data,"player0")].currentAnim = 0;
    }
    if(IsKeyReleased(KEY_DOWN) || IsKeyReleased(KEY_S))
    {
        data->session.render.model[MQFindRenderModel(*data,"player0")].reverse = false;
        data->session.render.model[MQFindRenderModel(*data,"player0")].currentAnim = 0;
    }
    if(IsKeyDown(KEY_SPACE))
    {
        data->game.player[0].position.y +=0.14;
    }
}
