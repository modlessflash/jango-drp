#include <iostream>
#include <chrono>
#include "discord-rpc/include/discord_rpc.h"
#include "discord-rpc/include/discord_register.h"
#include "httplib.h"

int main(){
  DiscordEventHandlers handlers;
  memset(&handlers, 0, sizeof(handlers));
  Discord_Initialize("1475413537001308160", &handlers, 1, NULL);

  httplib::Server svr;
  svr.Options(R"(\/jangodrp)",
    [&](const auto& req, auto& res)
    {
      res.set_header("Access-Control-Allow-Origin", "*");
      res.set_header("Access-Control-Allow-Headers", "*");
      res.set_header("Access-Control-Allow-Methods", "*");
      res.status = 200;
    }
  );

  svr.Get("/jangodrp",
    [&](const auto& req, auto& res)
    {
      res.set_header("Access-Control-Allow-Origin", "*");
      res.set_header("Access-Control-Allow-Headers", "*");
      res.set_header("Access-Control-Allow-Methods", "*");
      res.status = 200;

      if (req.has_param("artist") && req.has_param("title") && req.has_param("imgurl") && req.has_param("time") && req.has_param("playing"))
      {
        std::string playing = req.get_param_value("playing");
        if (playing == "1")
        {
          DiscordRichPresence pr;
          memset(&pr, 0, sizeof(pr));
          std::string artist  = req.get_param_value("artist");
          std::string title   = req.get_param_value("title");
          std::string imgurl  = req.get_param_value("imgurl");
          std::string time    = req.get_param_value("time");    

          pr.details         = artist.c_str();
          pr.state           = title.c_str();
          pr.startTimestamp  = std::stoll(time);
          pr.largeImageKey   = imgurl.c_str();

          pr.largeImageText = "jango-drp";
          Discord_UpdatePresence(&pr);
        }
        else Discord_ClearPresence();
      }
    }
  );

  svr.listen("127.0.0.1", 9294);
  Discord_Shutdown();
  return 0;
}