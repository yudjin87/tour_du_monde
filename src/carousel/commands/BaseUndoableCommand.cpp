#include <carousel/commands/BaseUndoableCommand.h>
#include <carousel/commands/IUndoStack.h>

BaseUndoableCommand::BaseUndoableCommand(IUndoStack *undoStack, QObject *parent)
    : IUndoableCommand(parent)
    , m_undoStack(undoStack)
    , m_text()
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

IUndoableCommand *BaseUndoableCommand::child(int)
{
    return nullptr;
}

const IUndoableCommand *BaseUndoableCommand::child(int) const
{
    return nullptr;
}

int BaseUndoableCommand::childCount() const
{
    return 0;
}

QString BaseUndoableCommand::text() const
{
    return m_text;
}

int BaseUndoableCommand::id() const
{
    return -1;
}

bool BaseUndoableCommand::mergeWith(const IUndoableCommand *other)
{
    Q_UNUSED(other)
    return false;
}

void BaseUndoableCommand::setText(const QString &text)
{
    m_text = text;
}
