#pragma once

enum ReqType
{
    BUTTON_PRESS,
};

class Req
{
    ReqType _req_type;

public:

    Req(ReqType req_type) : _req_type{req_type} {};
};