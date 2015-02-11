#include <carousel/commands/BaseUndoableCommand.h>
#include <carousel/commands/IUndoStack.h>

BaseUndoableCommand::BaseUndoableCommand(IUndoStack *undoStack)
    : IUndoableCommand()
    , m_undoStack(undoStack)
{
}

BaseUndoableCommand::~BaseUndoableCommand()
{
}

void BaseUndoableCommand::pushToStack()
{
    if (m_undoStack != nullptr) {
        m_undoStack->push(this);
        return;
    }

    redo();
    deleteLater();
}
