#include <carousel/commands/GroupUndoableCommand.h>

GroupUndoableCommand::GroupUndoableCommand(IUndoStack *undoStack, QObject *parent)
    : BaseUndoableCommand(undoStack, parent)
    , m_children()
{
}

GroupUndoableCommand::~GroupUndoableCommand()
{
    for (IUndoableCommand* child : m_children)
    {
        delete child;
    }

    m_children.clear();
}

void GroupUndoableCommand::addChild(IUndoableCommand *child)
{
    m_children.push_back(child);
}

IUndoableCommand *GroupUndoableCommand::child(int index)
{
    return m_children[index];
}

const IUndoableCommand *GroupUndoableCommand::child(int index) const
{
    return m_children[index];
}

int GroupUndoableCommand::childCount() const
{
    return m_children.size();
}

void GroupUndoableCommand::redo()
{
}

void GroupUndoableCommand::undo()
{
}
