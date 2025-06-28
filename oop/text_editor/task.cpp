#include "task.h"
#include "logged_command_wrapper.h"
#include <iostream>

CommandBuilder::CommandBuilder() 
    : logStreamPtr_(NULL)
    {}

CommandBuilder& CommandBuilder::WithType(CommandBuilder::Type type) {
    this->type_ = type;
    return *this;
}

CommandBuilder& CommandBuilder::SelectionSize(size_t SelectionSize) {
    this->selectionSize_ = SelectionSize;
    return *this;
}

CommandBuilder& CommandBuilder::Text(std::string text) {
    this->text_ = text;
    return *this;
}

CommandBuilder& CommandBuilder::LogTo(std::ostream& logStream) {
    this->logStreamPtr_ = &logStream;
    return *this;
}

CommandBuilder& CommandBuilder::AddSubcommand(CommandPtr subcommand) {
    this->subcommands_.push_back(subcommand);
    return *this;
}



CommandLoggerVisitor::CommandLoggerVisitor(std::ostream& logStream) 
    : logStream_(logStream)
    {}

void CommandLoggerVisitor::VisitMoveCursorLeftCommand(MoveCursorLeftCommand& command) {
    this->logStream_ << "h";
    return;
}

void CommandLoggerVisitor::VisitMoveCursorRightCommand(MoveCursorRightCommand& command) {
    this->logStream_ << "l";
    return;
}

void CommandLoggerVisitor::VisitMoveCursorUpCommand(MoveCursorUpCommand& command) {
    this->logStream_ << "k";
    return;
}

void CommandLoggerVisitor::VisitMoveCursorDownCommand(MoveCursorDownCommand& command) {
    this->logStream_ << "j";
    return;
}

void CommandLoggerVisitor::VisitSelectCommand(SelectTextCommand& command) {
    this->logStream_ << "v";
    return;
}

void CommandLoggerVisitor::VisitInsertTextCommand(InsertTextCommand& command) {
    this->logStream_ << "i";
    return;
}

void CommandLoggerVisitor::VisitDeleteTextCommand(DeleteTextCommand& command) {
    this->logStream_ << "d";
    return;
}

void CommandLoggerVisitor::VisitCopyTextCommand(CopyTextCommand& command) {
    this->logStream_ << "y";
    return;
}

void CommandLoggerVisitor::VisitPasteTextCommand(PasteTextCommand& command) {
    this->logStream_ << "p";
    return;
}

void CommandLoggerVisitor::VisitUppercaseTextCommand(UppercaseTextCommand& command) {
    this->logStream_ << "U";
    return;
}

void CommandLoggerVisitor::VisitLowercaseTextCommand(LowercaseTextCommand& command) {
    this->logStream_ << "u";
    return;
}

void CommandLoggerVisitor::VisitMoveToEndCommand(MoveToEndCommand& command) {
    this->logStream_ << "$";
    return;
}

void CommandLoggerVisitor::VisitMoveToStartCommand(MoveToStartCommand& command) {
    this->logStream_ << "0";
    return;
}

void CommandLoggerVisitor::VisitDeleteWordCommand(DeleteWordCommand& command) {
    this->logStream_ << "dE";
    return;
}


// class LoggedCommandWrapper : public ICommand {
// private:
//     CommandPtr command_;
//     std::ostream& logStream_;
// public:
//     LoggedCommandWrapper(std::ostream& logStream, CommandPtr command) 
//         : logStream_(logStream)
//         , command_(command)
//         {}

//     void Apply(std::string& buffer, size_t& cursorPosition, std::string& clipboard, TextEditor& editor) final {
//         command_->Apply(buffer, cursorPosition, clipboard, editor);
//     }
//     void AcceptVisitor(CommandVisitor& visitor) final {}
// };

/* Курсор влево */
class MoveCursorLeftCommand : public ICommand {
public:
    MoveCursorLeftCommand() = default;

    void Apply(std::string& buffer, size_t& cursorPosition, std::string& clipboard, TextEditor& editor) override {
        if (cursorPosition != 0) {
            cursorPosition--;
            if (editor.HasSelection() == true) {
                editor.UnselectText();
            }
        }
        if (editor.HasSelection() == true) {
            editor.UnselectText();
        }
    }
    void AcceptVisitor(CommandVisitor& visitor) override {
        visitor.VisitMoveCursorLeftCommand(*this);
    }
};

/* Курсор вправо */
class MoveCursorRightCommand : public ICommand {
public:
    MoveCursorRightCommand() = default;

    void Apply(std::string& buffer, size_t& cursorPosition, std::string& clipboard, TextEditor& editor) override {
        if (cursorPosition != buffer.size()) {
            cursorPosition++;
            if (editor.HasSelection() == true) {
                editor.UnselectText();
            }
        }
        if (editor.HasSelection() == true) {
            editor.UnselectText();
        }
    }
    void AcceptVisitor(CommandVisitor& visitor) override {
        visitor.VisitMoveCursorRightCommand(*this);
    }
};

/* Курсор вверх */
class MoveCursorUpCommand : public ICommand {
public:
    MoveCursorUpCommand() = default;

    void Apply(std::string& buffer, size_t& cursorPosition, std::string& clipboard, TextEditor& editor) override {
        size_t i = cursorPosition;
        while (i > 0 && buffer[i - 1] != '\n') {
            i--;
        }
        if (i == 0) {
            return;
        }
        else {
            size_t dif = cursorPosition - i;
            size_t j = i - 1;
            while (j > 0 && buffer[j - 1] != '\n') {
                j--;
            }
            size_t len = (i - 1) - j;
            if (len >= dif) {
                cursorPosition = j + dif;
            }
            else {
                cursorPosition = j + len;
            }
        }
        if (editor.HasSelection() == true) {
            editor.UnselectText();
        }
    }
    void AcceptVisitor(CommandVisitor& visitor) override {
        visitor.VisitMoveCursorUpCommand(*this);
    }
};

/* Курсор вниз */
class MoveCursorDownCommand : public ICommand {
public:
    MoveCursorDownCommand() = default;

    void Apply(std::string& buffer, size_t& cursorPosition, std::string& clipboard, TextEditor& editor) override {
        size_t i = cursorPosition;
        size_t j = cursorPosition;
        while (i < buffer.size() && buffer[i] != '\n') {
            i++;
        }
        while (j > 0 && buffer[j - 1] != '\n') {
            j--;
        }
        if (i == buffer.size()) {
            cursorPosition = i;
        }
        else {
            size_t dif = cursorPosition - j;
            size_t k = i + 1;
            while (k < buffer.size() && buffer[k] != '\n') {
                k++;
            }
            size_t len = k - i;
            if (len >= dif) {
                cursorPosition = i + 1 + dif;
            }
            else {
                cursorPosition = i + 1 + len;
            }
        }
        if (editor.HasSelection() == true) {
            editor.UnselectText();
        }
    }
    void AcceptVisitor(CommandVisitor& visitor) override {
        visitor.VisitMoveCursorDownCommand(*this);
    }
};

/* Выделить текст */
class SelectTextCommand : public ICommand {
private:
    size_t len;
public:
    SelectTextCommand(size_t len_)
        : len(len_)
        {}

    void Apply(std::string& buffer, size_t& cursorPosition, std::string& clipboard, TextEditor& editor) override {
        editor.SelectText(cursorPosition, cursorPosition + len);
    }
    void AcceptVisitor(CommandVisitor& visitor) override {
        visitor.VisitSelectCommand(*this);
    }
};

/* Ввести текст */
class InsertTextCommand : public ICommand {
private:
    std::string ins_str;
public:
    InsertTextCommand(std::string ins_str_) 
        : ins_str(ins_str_)
        {}
    
    void Apply(std::string& buffer, size_t& cursorPosition, std::string& clipboard, TextEditor& editor) override {
        if (editor.HasSelection() == true) {
            size_t beg = (editor.GetSelection()).first;
            size_t end = (editor.GetSelection()).second;
            buffer = buffer.substr(0, beg) + ins_str + buffer.substr(end, buffer.size() - beg);
            cursorPosition = beg;
            editor.UnselectText();
        }
        else {
            buffer = buffer.substr(0, cursorPosition) + ins_str + buffer.substr(cursorPosition, buffer.size() - cursorPosition);
            cursorPosition += ins_str.size(); 
        }
    }
    void AcceptVisitor(CommandVisitor& visitor) override {
        visitor.VisitInsertTextCommand(*this);
    }
};

/* Удалить текст */
class DeleteTextCommand : public ICommand {
public:
    DeleteTextCommand() = default;

    void Apply(std::string& buffer, size_t& cursorPosition, std::string& clipboard, TextEditor& editor) override {
        if (editor.HasSelection() == true) {
            size_t beg = (editor.GetSelection()).first;
            size_t end = (editor.GetSelection()).second;
            buffer.erase(buffer.begin() + beg, buffer.begin() + end + 1);
            cursorPosition = beg;
            editor.UnselectText();
        }
        else {
            buffer.erase(buffer.begin() + cursorPosition - 1);
            cursorPosition--;
        }
    }
    void AcceptVisitor(CommandVisitor& visitor) override {
        visitor.VisitDeleteTextCommand(*this);
    }
};

/* Скопировать текст */
class CopyTextCommand : public ICommand {
public:
    CopyTextCommand() = default;

    void Apply(std::string& buffer, size_t& cursorPosition, std::string& clipboard, TextEditor& editor) override {
        if (editor.HasSelection() == true) {
            clipboard = buffer.substr((editor.GetSelection()).first, (editor.GetSelection()).second - (editor.GetSelection()).first);
            cursorPosition = editor.GetSelection().first;
            editor.UnselectText();
        }
        else {
            clipboard = buffer[cursorPosition - 1];
        }
    }
    void AcceptVisitor(CommandVisitor& visitor) {
        visitor.VisitCopyTextCommand(*this);
    }
};

/* Вставить скопированный текст */
class PasteTextCommand : public ICommand {
public:
    PasteTextCommand() = default;

    void Apply(std::string& buffer, size_t& cursorPosition, std::string& clipboard, TextEditor& editor) override {
        if (editor.HasSelection() == true) {
            size_t beg = (editor.GetSelection()).first;
            size_t end = (editor.GetSelection()).second;
            buffer = buffer.substr(0, beg) + clipboard + buffer.substr(end, buffer.size() - end);
            size_t len = clipboard.size();
            cursorPosition = beg + len;
            editor.UnselectText();
        }
        else {
            buffer = buffer.substr(0, cursorPosition) + clipboard + buffer.substr(cursorPosition, buffer.size() - cursorPosition);
            cursorPosition += clipboard.size();
        }
    }
    void AcceptVisitor(CommandVisitor& visitor) override {
        visitor.VisitPasteTextCommand(*this);
    }
};

/* Привести выделенный текст в ВЕРХНИЙ регистр */
class UppercaseTextCommand : public ICommand {
public:
    UppercaseTextCommand() = default;

    void Apply(std::string& buffer, size_t& cursorPosition, std::string& clipboard, TextEditor& editor) override {
        if (editor.HasSelection() == true) {
            size_t beg = (editor.GetSelection()).first;
            size_t end = (editor.GetSelection()).second;
            for (size_t i = beg; i <= end; ++i) {
                buffer[i] = char(std::toupper(buffer[i]));
                // if (buffer[i] - 'a' >= 0) {
                //     buffer[i] = char('a' + (buffer[i] - 'A'));
                // }
            }
            editor.UnselectText();
        }
    }
    void AcceptVisitor(CommandVisitor& visitor) override {
        visitor.VisitUppercaseTextCommand(*this);
    }
};

/* Привести выделенный текст в нижний регистр */
class LowercaseTextCommand : public ICommand {
public:
    LowercaseTextCommand() = default;

    void Apply(std::string& buffer, size_t& cursorPosition, std::string& clipboard, TextEditor& editor) override {
        if (editor.HasSelection() == true) {
            size_t beg = (editor.GetSelection()).first;
            size_t end = (editor.GetSelection()).second;
            for (size_t i = beg; i <= end; ++i) {
                buffer[i] = char(std::tolower(buffer[i]));
            }
            editor.UnselectText();
        }
    }
    void AcceptVisitor(CommandVisitor& visitor) override {
        visitor.VisitLowercaseTextCommand(*this);
    }
};

/* Перенести курсор в конец строки */
class MoveToEndCommand : public ICommand {
public:
    MoveToEndCommand() = default;

    void Apply(std::string& buffer, size_t& cursorPosition, std::string& clipboard, TextEditor& editor) override {
        size_t i = cursorPosition;
        while (i != buffer.size() && buffer[i + 1] != '\n') {
            i++;
        }
        if (buffer.size() >= i + 2 && buffer[i + 1] == '\n') {
            cursorPosition = i + 1;
        }
        else {
            cursorPosition = i;
        }
        if (editor.HasSelection() == true) {
            editor.UnselectText();
        }
    }
    void AcceptVisitor(CommandVisitor& visitor) override {
        visitor.VisitMoveToEndCommand(*this);
    }
};

/* Перенести курсор в начало строки */
class MoveToStartCommand : public ICommand {
public:
    MoveToStartCommand() = default;

    void Apply(std::string& buffer, size_t& cursorPosition, std::string& clipboard, TextEditor& editor) override {
        size_t i = cursorPosition;
        while (i > 0 && buffer[i - 1] != '\n') {
            i--;
        }
        cursorPosition = i;
        if (editor.HasSelection() == true) {
            editor.UnselectText();
        }
    }
    void AcceptVisitor(CommandVisitor& visitor) override {
        visitor.VisitMoveToStartCommand(*this);
    }
};

/* Удалить часть строки, начиная от позиции курсора до первого пробела или конца строки */
class DeleteWordCommand : public ICommand {
public:
    DeleteWordCommand() = default;

    void Apply(std::string& buffer, size_t& cursorPosition, std::string& clipboard, TextEditor& editor) override {
        size_t i = cursorPosition;
        while (i < buffer.size() && buffer[i + 1] != ' ' && buffer[i + 1] != '\n') {
            i++;
        }
        buffer.erase(buffer.begin() + cursorPosition, buffer.begin() + i + 1);
        if (editor.HasSelection() == true) {
            editor.UnselectText();
        }
    }
    void AcceptVisitor(CommandVisitor& visitor) override {
        visitor.VisitDeleteWordCommand(*this);
    }
};

/* Макрос */
class MacroCommand : public ICommand {
private:
    std::list<CommandPtr> commands;
public:
    MacroCommand(std::list<CommandPtr>& commands_) 
        : commands(std::move(commands_))
        {}

    void Apply(std::string& buffer, size_t& cursorPosition, std::string& clipboard, TextEditor& editor) override {
        for (auto& command : commands) {
            editor.ApplyCommand(command);
        }
    }
    void AcceptVisitor(CommandVisitor &visitor) override {
        for (auto& command: commands) {
            command->AcceptVisitor(visitor);
        }
    }
};



CommandPtr CommandBuilder::build() {
    switch (this->type_) {
        case CommandBuilder::Type::MoveCursorLeft:
            if (this->logStreamPtr_ != NULL) {
                return std::make_shared<LoggedCommandWrapper>(LoggedCommandWrapper(*(this->logStreamPtr_), std::make_shared<MoveCursorLeftCommand>(MoveCursorLeftCommand())));
            }
            else {
                return std::make_shared<MoveCursorLeftCommand>(MoveCursorLeftCommand());
            }

        case CommandBuilder::Type::MoveCursorRight:
            if (this->logStreamPtr_ != NULL) {
                return std::make_shared<LoggedCommandWrapper>(LoggedCommandWrapper(*(this->logStreamPtr_), std::make_shared<MoveCursorRightCommand>(MoveCursorRightCommand())));
            }
            else {
                return std::make_shared<MoveCursorRightCommand>(MoveCursorRightCommand());
            }

        case CommandBuilder::Type::MoveCursorUp:
            if (this->logStreamPtr_ != NULL) {
                return std::make_shared<LoggedCommandWrapper>(LoggedCommandWrapper(*(this->logStreamPtr_), std::make_shared<MoveCursorUpCommand>(MoveCursorUpCommand())));
            }
            else {
                return std::make_shared<MoveCursorUpCommand>(MoveCursorUpCommand());
            }

        case CommandBuilder::Type::MoveCursorDown:
            if (this->logStreamPtr_ != NULL) {
                return std::make_shared<LoggedCommandWrapper>(LoggedCommandWrapper(*(this->logStreamPtr_), std::make_shared<MoveCursorDownCommand>(MoveCursorDownCommand())));
            }
            else {
                return std::make_shared<MoveCursorDownCommand>(MoveCursorDownCommand());
            }

        case CommandBuilder::Type::SelectText:
            if (this->logStreamPtr_ != NULL) {
                return std::make_shared<LoggedCommandWrapper>(LoggedCommandWrapper(*(this->logStreamPtr_), std::make_shared<SelectTextCommand>(SelectTextCommand(this->selectionSize_))));
            }
            else {
                return std::make_shared<SelectTextCommand>(SelectTextCommand(this->selectionSize_));
            }
        
        case CommandBuilder::Type::InsertText:
            if (this->logStreamPtr_ != NULL) {
                return std::make_shared<LoggedCommandWrapper>(LoggedCommandWrapper(*(this->logStreamPtr_), std::make_shared<InsertTextCommand>(InsertTextCommand(this->text_))));
            }
            else {
                return std::make_shared<InsertTextCommand>(InsertTextCommand(this->text_));
            }

        case CommandBuilder::Type::DeleteText:
            if (this->logStreamPtr_ != NULL) {
                return std::make_shared<LoggedCommandWrapper>(LoggedCommandWrapper(*(this->logStreamPtr_), std::make_shared<DeleteTextCommand>(DeleteTextCommand())));
            }
            else {
                return std::make_shared<DeleteTextCommand>(DeleteTextCommand());
            }

        case CommandBuilder::Type::CopyText:
            if (this->logStreamPtr_ != NULL) {
                return std::make_shared<LoggedCommandWrapper>(LoggedCommandWrapper(*(this->logStreamPtr_), std::make_shared<CopyTextCommand>(CopyTextCommand())));
            }
            else {
                return std::make_shared<CopyTextCommand>(CopyTextCommand());
            }

        case CommandBuilder::Type::PasteText:
            if (this->logStreamPtr_ != NULL) {
                return std::make_shared<LoggedCommandWrapper>(LoggedCommandWrapper(*(this->logStreamPtr_), std::make_shared<PasteTextCommand>(PasteTextCommand())));
            }
            else {
                return std::make_shared<PasteTextCommand>(PasteTextCommand());
            }
        
        case CommandBuilder::Type::UppercaseText:
            if (this->logStreamPtr_ != NULL) {
                return std::make_shared<LoggedCommandWrapper>(LoggedCommandWrapper(*(this->logStreamPtr_), std::make_shared<UppercaseTextCommand>(UppercaseTextCommand())));
            }
            else {
                return std::make_shared<UppercaseTextCommand>(UppercaseTextCommand());
            }

        case CommandBuilder::Type::LowercaseText:
            if (this->logStreamPtr_ != NULL) {
                return std::make_shared<LoggedCommandWrapper>(LoggedCommandWrapper(*(this->logStreamPtr_), std::make_shared<LowercaseTextCommand>(LowercaseTextCommand())));
            }
            else {
                return std::make_shared<LowercaseTextCommand>(LowercaseTextCommand());
            }
        
        case CommandBuilder::Type::MoveToEnd:
            if (this->logStreamPtr_ != NULL) {
                return std::make_shared<LoggedCommandWrapper>(LoggedCommandWrapper(*(this->logStreamPtr_), std::make_shared<MoveToEndCommand>(MoveToEndCommand())));
            }
            else {
                return std::make_shared<MoveToEndCommand>(MoveToEndCommand());
            }

        case CommandBuilder::Type::MoveToStart:
            if (this->logStreamPtr_ != NULL) {
                return std::make_shared<LoggedCommandWrapper>(LoggedCommandWrapper(*(this->logStreamPtr_), std::make_shared<MoveToStartCommand>(MoveToStartCommand())));
            }
            else {
                return std::make_shared<MoveToStartCommand>(MoveToStartCommand());
            }

        case CommandBuilder::Type::DeleteWord:
            if (this->logStreamPtr_ != NULL) {
                return std::make_shared<LoggedCommandWrapper>(LoggedCommandWrapper(*(this->logStreamPtr_), std::make_shared<DeleteWordCommand>(DeleteWordCommand())));
            }
            else {
                return std::make_shared<DeleteWordCommand>(DeleteWordCommand());
            }

        case CommandBuilder::Type::Macro:
            if (this->logStreamPtr_ != NULL) {
                return std::make_shared<LoggedCommandWrapper>(LoggedCommandWrapper(*(this->logStreamPtr_), std::make_shared<MacroCommand>(MacroCommand(this->subcommands_))));
            }
            else {
                return std::make_shared<MacroCommand>(MacroCommand(this->subcommands_));
            }
    }
    return nullptr;
}