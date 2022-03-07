/*
 * BreakoutGameLevel.cpp
 *
 *  Created on: Mar 6, 2022
 *      Author: Jordan Hunt
 */
#include <Breakout/BreakoutGameLevel.h>
BreakoutGameLevel::BreakoutGameLevel()
{
}
void BreakoutGameLevel::Initialize(const AxisAlignedRectangle &boundary)
{
    CreateDefaultTestLevel(boundary);
}
void BreakoutGameLevel::Load(const std::vector<Block> &blocks)
{
    this->blocks.clear();
    this->blocks = blocks;
}
void BreakoutGameLevel::Update(uint32_t deltaTime, Ball &ball)
{
    std::vector<Block> collidedBlocks;
    BoundaryEdge edgeToBounceOffOf;
    Block *blockToBoundOffOf = nullptr;
    float largestMagnitude = -1.0f;
    // Find all the blocks ball collided with
    for (auto &block : blocks)
    {
        BoundaryEdge blockEdge;
        if (!block.IsDestroyed() && block.HasCollided(ball.GetBoundingBox(), blockEdge))
        {
            collidedBlocks.push_back(block);
            float magnitude = block.GetCollisionOffset(ball.GetBoundingBox()).Magnitude();
            if (magnitude > largestMagnitude)
            {
                edgeToBounceOffOf = blockEdge;
                blockToBoundOffOf = &block;
            }
        }
    }
    // Only bounce off the "most" collided with block
    if (blockToBoundOffOf != nullptr)
    {
        blockToBoundOffOf->Bounce(ball, edgeToBounceOffOf);
        blockToBoundOffOf->ReduceHitpoints();
    }
    // Bounce off that block. Make flush with that block
    for (const auto &block : collidedBlocks)
    {
        BoundaryEdge edge;
        if (block.HasCollided(ball.GetBoundingBox(), edge))
        {
            Vector2D point;
            ball.MakeFlushWithEdge(edge, point, true);
        }
    }
}
void BreakoutGameLevel::Draw(Screen &screen)
{
    for (auto &block : blocks)
    {
        if (!block.IsDestroyed())
        {
            block.Draw(screen);
        }
    }
}
void BreakoutGameLevel::CreateDefaultTestLevel(const AxisAlignedRectangle &boundary)
{
    blocks.clear();
    const int NUMBER_OF_BLOCKS_ACROSS = ((int) boundary.GetWidth() - ((BLOCK_WIDTH))) / BLOCK_WIDTH;
    const int NUMBER_OF_BLOCK_ROWS = 5;
    float startX = ((int) boundary.GetWidth() - (NUMBER_OF_BLOCKS_ACROSS * (BLOCK_WIDTH + 1))) / 2;
    Color colors[NUMBER_OF_BLOCK_ROWS];
    colors[0] = Color::Red();
    colors[1] = Color::Pink();
    colors[2] = Color::Magenta();
    colors[3] = Color::Green();
    colors[4] = Color::Yellow();

    // Place the blocks
    for (int rows = 0; rows < NUMBER_OF_BLOCK_ROWS; rows++)
    {
        AxisAlignedRectangle blockRectangle = { Vector2D(startX, BLOCK_HEIGHT * (rows + 1)), BLOCK_WIDTH, BLOCK_HEIGHT };
        for (int columns = 0; columns < NUMBER_OF_BLOCKS_ACROSS; columns++)
        {
            Block block;
            block.Initialize(blockRectangle, 1, Color::Black(), colors[rows]);
            blocks.push_back(block);
            blockRectangle.MoveByDeltaOffset(Vector2D(BLOCK_WIDTH, 0));
        }
    }
}
