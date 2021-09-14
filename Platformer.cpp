
#include "Functions.h"


int main()
{
    SetConfigFlags(FLAG_WINDOW_RESIZABLE);
    InitWindow(screenwidth, screenheight, "Pile of shit");
    #include "Textures.h"

    // Chunk Generator
    for (int cy = 0; cy < chunksize; cy++)
    {
        for (int cx = 0; cx < chunksize; cx++)
        {
            tc = 0;
            tilepos = chunkpos;
            tilerect.x = chunkpos.x, tilerect.y = chunkpos.y + 60;

            chunkcoord.x = cx * tilesize;
            chunkcoord.y = cy * tilesize;

            coord = chunkcoord;

            // Tile Generator
            for (int ty = 0; ty < tilesize; ty++)
            {
                for (int tx = 0; tx < tilesize; tx++)
                {
                    // Set Tile Values
                    r = GetRandomValue(0, 3);

                    m.insert(std::make_pair<Coord, Coord>(Coord{ (int)coord.x, (int)coord.y }, Coord{ cc,tc }));   // Add index m

                    if (r == 0)chunkarray[cc].tilearray[tc].biome = "Water",  chunkarray[cc].tilearray[tc].tex = WaterTileTexture;
                    if (r == 1)chunkarray[cc].tilearray[tc].biome = "Grass",  chunkarray[cc].tilearray[tc].tex = GrassTileTexture;
                    if (r == 2)chunkarray[cc].tilearray[tc].biome = "Mount",  chunkarray[cc].tilearray[tc].tex = MountTileTexture;
                    if (r == 3)chunkarray[cc].tilearray[tc].biome = "Desert", chunkarray[cc].tilearray[tc].tex = DesertTileTexture;

                    chunkarray[cc].tilearray[tc].coord = coord;
                    chunkarray[cc].tilearray[tc].pos = tilepos;
                    chunkarray[cc].tilearray[tc].center = Vector2Add(tilepos, { 64,96 });
                    chunkarray[cc].tilearray[tc].rect = tilerect;


                    if (alternator == false)
                    {

                        alternator = true;
                        tilepos.y += 32;
                        tilerect.y += 34;
                    }
                    else
                    {
                        alternator = false;
                        tilepos.y -= 32;
                        tilerect.y -= 34;
                    }


                    coord.x++;

                    tilepos.x += 96;
                    tilerect.x += 96;
                    tc++;
                }

                coord.x = chunkcoord.x;
                coord.y++;

                tilepos.x = chunkpos.x;
                tilepos.y += 64;
                tilerect.x = chunkpos.x;
                tilerect.y += 64;
            }


            chunkarray[cc].pos = chunkpos;
            chunkpos.x = (98.0f * tilesize) * (cx + 1);
            cc++;
        }

        chunkpos.x = 0;
        chunkpos.y = (66.0f * tilesize) * (cy + 1);
    }

    // Initialize camera
    screensize = { (float)GetScreenWidth(), (float)GetScreenHeight() };
    screencenter = Vector2Divide(screensize, { 2,2 });
    Camera2D camera = { 0 };
    camera.zoom = 1.0f;
    camera.offset = { (float)GetScreenWidth() / 2, (float)GetScreenHeight() / 2 };
    camera.target = Vector2Add(camera.position, { (float)GetScreenWidth() / 2, (float)GetScreenHeight() / 2 });


    
    
    

    while (!WindowShouldClose())
    {
        // Physics Process
        nexttime = GetTime();
        if (nexttime > basetime + 0.01666)
        {
            basetime = nexttime;
        
            // Camera position controls
            zoomlevel = Remap(camera.zoom, 0.0f, 2.0f, 2.0f, 0.0f);
            if (IsKeyDown(KEY_W)) camera.position.y -= zoomlevel * 10;
            if (IsKeyDown(KEY_S)) camera.position.y += zoomlevel * 10;
            if (IsKeyDown(KEY_A)) camera.position.x -= zoomlevel * 10;
            if (IsKeyDown(KEY_D)) camera.position.x += zoomlevel * 10;
            // Camera zoom controls
            if (IsKeyDown(KEY_UP)) camera.zoom = 1.0f;
            if (IsKeyDown(KEY_DOWN)) camera.zoom = 0.5f;
            if (camera.zoom > 2.0f) camera.zoom = 2.0f;
            else if (camera.zoom < 0.1f) camera.zoom = 0.1f;
            // Update camera position and target
            screenwidth = GetScreenWidth(); screenheight = GetScreenHeight();
            screencenter = { (float)GetScreenWidth() / 2, (float)GetScreenHeight() / 2 };
            camera.target = Vector2Add(camera.position, screencenter);
        }

        BeginDrawing();

        BeginMode2D(camera);

        ClearBackground(RAYWHITE);
        
        mp = Vector2Add(GetMousePosition(), Vector2Subtract(camera.target, { (float)GetScreenWidth() / 2, (float)GetScreenHeight() / 2 }));
        distance = 1000;


        // Tile Loop Process
        for (int c = 0; c < chunksize * chunksize; c++)
        {
            if (Vector2Distance(camera.target, Vector2Add(chunkarray[c].pos, { 1600,1100 })) < 2500)
            {
                for (int t = 0; t < tilesize * tilesize; t++)
                {
                    // Render only elements that can be visible on screen
                    if (CheckCollisionRecs({ camera.position.x,camera.position.y,screensize.x,screensize.y }, chunkarray[c].tilearray[t].rect))  
                    //if (Vector2Distance(camera.target, chunkarray[c].tilearray[t].center) < 600)              <- |OLD CIRCULAR CULL FUNCTION|
                    { 
                        // Draw the tile textures
                        DrawTextureV(chunkarray[c].tilearray[t].tex, chunkarray[c].tilearray[t].pos, chunkarray[c].tilearray[t].col);
                        // Draw the tile coords
                        DrawText(TextFormat("%i", (int)chunkarray[c].tilearray[t].coord.x), (int)chunkarray[c].tilearray[t].center.x -20, (int)chunkarray[c].tilearray[t].center.y -10, 20, RED);
                        DrawText(TextFormat("%i", (int)chunkarray[c].tilearray[t].coord.y), (int)chunkarray[c].tilearray[t].center.x +10, (int)chunkarray[c].tilearray[t].center.y -10, 20, GREEN);

                        // Detect the tile under the cursor as closesttile
                        if (CheckCollisionPointRec(mp, chunkarray[c].tilearray[t].rect) && Vector2Distance(mp, chunkarray[c].tilearray[t].center) < distance)
                        {
                            distance = Vector2Distance(mp, chunkarray[c].tilearray[t].center);
                            closesttile = chunkarray[c].tilearray[t];

                            // Set tile
                            if (distance != 1000)
                            {
                                if (IsKeyDown(KEY_ONE))   chunkarray[c].tilearray[t].tex = GrassTileTexture, chunkarray[c].tilearray[t].biome = "Grass";
                                if (IsKeyDown(KEY_TWO))   chunkarray[c].tilearray[t].tex = MountTileTexture, chunkarray[c].tilearray[t].biome = "Mount";
                                if (IsKeyDown(KEY_THREE)) chunkarray[c].tilearray[t].tex = WaterTileTexture, chunkarray[c].tilearray[t].biome = "Water";
                                if (IsKeyDown(KEY_FOUR)) chunkarray[c].tilearray[t].tex = DesertTileTexture, chunkarray[c].tilearray[t].biome = "Desert";
                            }
                        }
                    }
                }
            }
        }
        // Draw highlight on closesttile
        DrawTextureV(HighlightTileTexture, closesttile.pos, WHITE);


        if (IsMouseButtonPressed(0))
        {
            frontier.clear(); old.clear(); next.clear();
            frontier.push_back({(int)closesttile.coord.x, (int)closesttile.coord.y}); //old.push_back({ (int)closesttile.coord.x, (int)closesttile.coord.y });


            //std::cout << chunkarray[m[{frontier[0].x, frontier[0].y}].x].tilearray[m[{frontier[0].x, frontier[0].y}].y].biome << std::endl;

            //std::cout << "Chunk: " << m[{current[0].x, current[0].y}].x << std::endl;
            //std::cout << "Tile: " << m[{current[0].x, current[0].y}].y << std::endl;
            
            for (int i = 0; i < 1; i++)                                                              // for every iteration...
            {
                for (int f = 0; f < frontier.size(); f++)                                               // for every frontier tile...
                {
                    if (!(frontier[f].x % 2))                                                               // if pair...
                    {
                        et[0] = { frontier[f].x + 1, frontier[f].y + 0 };                                       // create expansion tiles
                        et[1] = { frontier[f].x + 0, frontier[f].y + 1 };                                       //          #
                        et[2] = { frontier[f].x - 1, frontier[f].y - 1 };                                       //          #
                        et[3] = { frontier[f].x + 0, frontier[f].y - 1 };                                       //          #
                        et[4] = { frontier[f].x + 1, frontier[f].y - 1 };                                       //          #
                        et[5] = { frontier[f].x - 1, frontier[f].y + 0 };                                       //          #

                        for (int t = 0; t < 6; t++)                                                             // for every expansion tile...
                        {
                            next.push_back(et[t]);
                        }
                    }
                //    else                                                                                    // if odd...
                //    {
                //        et[0] = { frontier[f].x + 0, frontier[f].y - 1 };                                       // create expansion tiles
                //        et[1] = { frontier[f].x + 1, frontier[f].y + 0 };                                       //          #
                //        et[2] = { frontier[f].x + 1, frontier[f].y + 1 };                                       //          #
                //        et[3] = { frontier[f].x + 0, frontier[f].y + 1 };                                       //          #
                //        et[4] = { frontier[f].x - 1, frontier[f].y + 1 };                                       //          #
                //        et[5] = { frontier[f].x - 1, frontier[f].y + 0 };                                       //          #

                //        for (int t = 0; t < 6; t++)                                                             // for every expansion tile...
                //        {
                //            for (int u = 0; u < old.size(); u++)                                                // for every tile in old...
                //            {
                //                if (!(CoordEqual(et[t], frontier[u]))) add = true; else add = false;                // Check if they are equal and add to next if not
                //            }
                //            for (int j = 0; j < next.size(); j++)                                                // for every tile in next...
                //            {
                //                if (!(CoordEqual(et[t], frontier[j]))) add = true; else add = false;                // Check if they are equal and add to next if not
                //            }
                //            if (add) frontier.push_back(et[t]), old.push_back(et[t]);                            // if add is true push back to frontier and old
                //        }
                //    }
                //    
                }


                // shuffle the vectors

                //for (int i = 0; i < frontier.size(); i++) old.push_back(frontier[i]); //frontier.clear(); // add every frontier tile to old and then clear frontier

                //for (int i = 0; i < next.size(); i++) frontier.push_back(frontier[i]); //next.clear();    // add every next tile to frontier and then clear next


                std::cout << "old: " << old.size() << std::endl;
                std::cout << "frontier: " << frontier.size() << std::endl;
                std::cout << "next: " << next.size() << std::endl;


            }
        }

        //for (int i = 0; i < old.size(); i++)
        //{
        //    DrawCircleV(chunkarray[m[{frontier[i].x, frontier[i].y}].x].tilearray[m[{frontier[i].x, frontier[i].y}].y].center, 20, PURPLE);
        //}

        //for (int i = 0; i < frontier.size(); i++)
        //{
        //    DrawCircleV(chunkarray[m[{frontier[i].x, frontier[i].y}].x].tilearray[m[{frontier[i].x, frontier[i].y}].y].center, 10, RED);
        //}

        for (int i = 0; i < next.size(); i++)
        {
            DrawCircleV(chunkarray[0].tilearray[0].center, 10, GREEN);
            //std::cout << next.size() << std::endl;
        }

        DrawText(TextFormat("%2i", (int)closesttile.coord.x), (int)camera.position.x + 10, (int)camera.position.y + 30, 20, GRAY);
        DrawText(TextFormat("%2i", (int)closesttile.coord.y), (int)camera.position.x + 10, (int)camera.position.y + 50, 20, GRAY);
        DrawFPS((int)camera.position.x + 10, (int)camera.position.y + 10);
        EndMode2D();
        EndDrawing();
    }

    CloseWindow();
    return 0;
}