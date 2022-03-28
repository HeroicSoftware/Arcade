/*
 * BreakoutGameLevel.cpp
 *
 *  Created on: Mar 6, 2022
 *      Author: Jordan Hunt
 */
#include "Breakout/BreakoutGameLevel.h"
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
    const int NUMBER_OF_BLOCKS_ACROSS = ((int) boundary.GetWidth() - (2 * (BLOCK_WIDTH))) / BLOCK_WIDTH;
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
struct LayoutBlock
{
        char symbol = '-';
        int hitPoints = 0;
        Color color = Color::Black();
};
LayoutBlock FindLayoutBlockForSymbol(const std::vector<LayoutBlock> &blocks, char symbol)
{
    for (size_t i = 0; i < blocks.size(); i++)
    {
        if (blocks[i].symbol == symbol)
        {
            return blocks[i];
        }
    }
    return LayoutBlock();
}
std::vector<BreakoutGameLevel> BreakoutGameLevel::LoadLevelsFromFile(const std::string &filePath)
{
    std::vector<BreakoutGameLevel> gameLevels;
    std::vector<LayoutBlock> levelLayoutBlocks;
    std::vector<Block> levelBlocks;
    int width = 0;
    int height = 0;
    FileCommandLoader fileLoader;
    Command levelCommand;
    levelCommand.commandString = "level";
    levelCommand.parseFunction = [&](ParseFunctionParameters parameters)
    {
        if (gameLevels.size() > 0)
        {
            gameLevels.back().Load(levelBlocks);
        }
        // Clear everything to reset
        levelLayoutBlocks.clear();
        levelBlocks.clear();
        width = 0;
        height = 0;
        BreakoutGameLevel level;
        level.Initialize(AxisAlignedRectangle(Vector2D::Zero, Application::Singleton().GetWidth(), Application::Singleton().GetHeight()));
        gameLevels.push_back(level);
    };
    fileLoader.AddCommand(levelCommand);
    Command blockCommand;
    blockCommand.commandString = "block";
    blockCommand.parseFunction = [&](ParseFunctionParameters parameters)
    {
        LayoutBlock layoutBlock;
        levelLayoutBlocks.push_back(layoutBlock);
    };
    fileLoader.AddCommand(blockCommand);
    Command symbolCommand;
    symbolCommand.commandString = "symbol";
    symbolCommand.parseFunction = [&](ParseFunctionParameters parameters)
    {
        levelLayoutBlocks.back().symbol = FileCommandLoader::ReadCharacter(parameters);
    };
    fileLoader.AddCommand(symbolCommand);
    Command fillColorCommand;
    fillColorCommand.commandString = "fillcolor";
    fillColorCommand.parseFunction = [&](ParseFunctionParameters parameters)
    {
        levelLayoutBlocks.back().color = FileCommandLoader::ReadColor(parameters);
    };
    fileLoader.AddCommand(fillColorCommand);
    Command hitPointsCommand;
    hitPointsCommand.commandString = "hp";
    hitPointsCommand.parseFunction = [&](ParseFunctionParameters parameters)
    {
        levelLayoutBlocks.back().hitPoints = FileCommandLoader::ReadInteger(parameters);
    };
    fileLoader.AddCommand(hitPointsCommand);
    Command widthCommad;
    widthCommad.commandString = "width";
    widthCommad.parseFunction = [&](ParseFunctionParameters parameters)
    {
        width = FileCommandLoader::ReadInteger(parameters);
    };
    fileLoader.AddCommand(widthCommad);
    Command heightCommad;
    heightCommad.commandString = "height";
    heightCommad.parseFunction = [&](ParseFunctionParameters parameters)
    {
        height = FileCommandLoader::ReadInteger(parameters);
    };
    Command layoutCommand;
    layoutCommand.commandType = COMMAND_MULTIPLE_LINE;
    layoutCommand.commandString = "layout";
    layoutCommand.parseFunction = [&](ParseFunctionParameters parameters)
    {
        float startingX = 0;
        AxisAlignedRectangle blockRectangle(Vector2D(startingX, (parameters.lineNumber + 1) * BLOCK_HEIGHT), BLOCK_WIDTH, BLOCK_HEIGHT);
        for (size_t character = 0; character < parameters.line.length(); character++)
        {
            if (parameters.line[character] != '-')
            {
                LayoutBlock layoutBlock = FindLayoutBlockForSymbol(levelLayoutBlocks, parameters.line[character]);
                Block block;
                block.Initialize(blockRectangle, layoutBlock.hitPoints, Color::Black(), layoutBlock.color);
                levelBlocks.push_back(block);
            }
            blockRectangle.MoveByDeltaOffset(Vector2D(BLOCK_WIDTH, 0));
        }
    };
    fileLoader.AddCommand(layoutCommand);
    fileLoader.LoadFile(filePath);
    if (gameLevels.size() > 0)
    {
        gameLevels.back().Load(levelBlocks);
    }
    return gameLevels;
}

bool BreakoutGameLevel::IsLevelComplete() const
{
    for (size_t i = 0; i < blocks.size(); i++)
    {
        if (!blocks[i].IsDestroyed() && blocks[i].GetHitpoints() != Block::UNBREAKABLE)
        {
            return false;
        }
    }
    return true;
}
