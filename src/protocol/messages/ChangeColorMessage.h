//
// Created by Emilson Filho on 05/08/2026.
//

#ifndef CONEXAO98_CHANGECOLORMESSAGE_H
#define CONEXAO98_CHANGECOLORMESSAGE_H
#include "../Message.h"
#include "../UserColor.h"


class ChangeColorMessage : public Message {
private:
    UserColor newColor;
public:
    explicit ChangeColorMessage(UserColor newColor);

    MessageType getType() override;
    ByteArray serialize() override;

    [[nodiscard]] UserColor getColor() const;
};


#endif //CONEXAO98_CHANGECOLORMESSAGE_H