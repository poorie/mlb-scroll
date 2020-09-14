//  To parse this JSON data, first install
//
//      json.hpp  https://github.com/nlohmann/json
//
//  Then include this file, and then do
//
//     StatsApi data = nlohmann::json::parse(jsonString);

#pragma once

#include <nlohmann/json.hpp>

#ifndef NLOHMANN_OPT_HELPER
#define NLOHMANN_OPT_HELPER
namespace nlohmann {
    template <typename T>
    struct adl_serializer<std::shared_ptr<T>> {
        static void to_json(json & j, const std::shared_ptr<T> & opt) {
            if (!opt) j = nullptr; else j = *opt;
        }

        static std::shared_ptr<T> from_json(const json & j) {
            if (j.is_null()) return std::unique_ptr<T>(); else return std::unique_ptr<T>(new T(j.get<T>()));
        }
    };
}
#endif

namespace quicktype {
    using nlohmann::json;

    inline json get_untyped(const json & j, const char * property) {
        if (j.find(property) != j.end()) {
            return j.at(property).get<json>();
        }
        return json();
    }

    inline json get_untyped(const json & j, std::string property) {
        return get_untyped(j, property.data());
    }

    template <typename T>
    inline std::shared_ptr<T> get_optional(const json & j, const char * property) {
        if (j.find(property) != j.end()) {
            return j.at(property).get<std::shared_ptr<T>>();
        }
        return std::shared_ptr<T>();
    }

    template <typename T>
    inline std::shared_ptr<T> get_optional(const json & j, std::string property) {
        return get_optional<T>(j, property.data());
    }

    struct Contributor {
        std::shared_ptr<std::string> name;
        std::shared_ptr<std::string> tagline;
    };

    enum class AspectRatio : int { THE_169, THE_43, THE_6427 };

    struct Cut {
        std::shared_ptr<AspectRatio> aspect_ratio;
        std::shared_ptr<int64_t> width;
        std::shared_ptr<int64_t> height;
        std::shared_ptr<std::string> src;
        std::shared_ptr<std::string> at2_x;
        std::shared_ptr<std::string> at3_x;
    };

    struct Image {
        std::shared_ptr<std::string> title;
        std::shared_ptr<std::string> alt_text;
        std::shared_ptr<std::vector<Cut>> cuts;
    };

    enum class Type : int { BODY_PARAGRAPH_COUNT, CUSTOMENTITY_CONTRIBUTOR, GAME, GAME_PK, PLAYER, PLAYER_ID, SEASON, TAXONOMY, TEAM, TEAM_ID };

    struct KeywordsAll {
        std::shared_ptr<Type> type;
        std::shared_ptr<std::string> value;
        std::shared_ptr<std::string> display_name;
    };

    enum class Name : int { HIGH_BIT, HLS_CLOUD, HTTP_CLOUD_WIRED, HTTP_CLOUD_WIRED_60, MP4_AVC };

    struct Playback {
        std::shared_ptr<Name> name;
        std::shared_ptr<std::string> url;
        std::shared_ptr<std::string> width;
        std::shared_ptr<std::string> height;
    };

    struct MlbMedia {
        std::shared_ptr<std::string> type;
        std::shared_ptr<std::string> state;
        std::shared_ptr<std::string> date;
        std::shared_ptr<std::string> id;
        std::shared_ptr<std::string> headline;
        std::shared_ptr<std::string> seo_title;
        std::shared_ptr<std::string> slug;
        std::shared_ptr<std::string> blurb;
        std::shared_ptr<std::vector<KeywordsAll>> keywords_all;
        std::shared_ptr<std::vector<nlohmann::json>> keywords_display;
        std::shared_ptr<Image> image;
        std::shared_ptr<bool> no_index;
        std::shared_ptr<std::string> media_playback_id;
        std::shared_ptr<std::string> title;
        std::shared_ptr<std::string> description;
        std::shared_ptr<std::string> duration;
        std::shared_ptr<std::string> media_playback_url;
        std::shared_ptr<std::vector<Playback>> playbacks;
        std::shared_ptr<std::string> cclocation_vtt;
        std::shared_ptr<std::string> guid;
    };

    struct Mlb {
        std::shared_ptr<std::string> type;
        std::shared_ptr<std::string> state;
        std::shared_ptr<std::string> date;
        std::shared_ptr<std::string> headline;
        std::shared_ptr<std::string> seo_title;
        std::shared_ptr<std::string> slug;
        std::shared_ptr<std::string> blurb;
        std::shared_ptr<std::vector<KeywordsAll>> keywords_all;
        std::shared_ptr<std::vector<nlohmann::json>> keywords_display;
        std::shared_ptr<Image> image;
        std::shared_ptr<std::string> seo_keywords;
        std::shared_ptr<std::string> body;
        std::shared_ptr<std::vector<Contributor>> contributors;
        std::shared_ptr<Image> photo;
        std::shared_ptr<std::string> url;
        std::shared_ptr<MlbMedia> media;
        std::shared_ptr<std::string> subhead;
    };

    struct Recap {
        std::shared_ptr<Mlb> mlb;
    };

    struct Editorial {
        std::shared_ptr<Recap> recap;
    };

    struct GameNotes {
    };

    struct ContentMedia {
        std::shared_ptr<bool> free_game;
        std::shared_ptr<bool> enhanced_game;
    };

    struct Content {
        std::shared_ptr<std::string> link;
        std::shared_ptr<Editorial> editorial;
        std::shared_ptr<ContentMedia> media;
        std::shared_ptr<GameNotes> highlights;
        std::shared_ptr<GameNotes> summary;
        std::shared_ptr<GameNotes> game_notes;
    };

    struct Loser {
        std::shared_ptr<int64_t> id;
        std::shared_ptr<std::string> full_name;
        std::shared_ptr<std::string> link;
    };

    struct Decisions {
        std::shared_ptr<Loser> winner;
        std::shared_ptr<Loser> loser;
        std::shared_ptr<Loser> save;
    };

    struct Status {
        std::shared_ptr<std::string> abstract_game_state;
        std::shared_ptr<std::string> coded_game_state;
        std::shared_ptr<std::string> detailed_state;
        std::shared_ptr<std::string> status_code;
        std::shared_ptr<std::string> abstract_game_code;
        std::shared_ptr<std::string> reason;
    };

    struct LeagueRecord {
        std::shared_ptr<int64_t> wins;
        std::shared_ptr<int64_t> losses;
        std::shared_ptr<std::string> pct;
    };

    struct Venue {
        std::shared_ptr<int64_t> id;
        std::shared_ptr<std::string> name;
        std::shared_ptr<std::string> link;
    };

    struct Away {
        std::shared_ptr<LeagueRecord> league_record;
        std::shared_ptr<int64_t> score;
        std::shared_ptr<Venue> team;
        std::shared_ptr<bool> is_winner;
        std::shared_ptr<bool> split_squad;
        std::shared_ptr<int64_t> series_number;
    };

    struct Teams {
        std::shared_ptr<Away> away;
        std::shared_ptr<Away> home;
    };

    struct Game {
        std::shared_ptr<int64_t> game_pk;
        std::shared_ptr<std::string> link;
        std::shared_ptr<std::string> game_type;
        std::shared_ptr<std::string> season;
        std::shared_ptr<std::string> game_date;
        std::shared_ptr<std::string> official_date;
        std::shared_ptr<Status> status;
        std::shared_ptr<Teams> teams;
        std::shared_ptr<Decisions> decisions;
        std::shared_ptr<Venue> venue;
        std::shared_ptr<Content> content;
        std::shared_ptr<bool> is_tie;
        std::shared_ptr<int64_t> game_number;
        std::shared_ptr<bool> public_facing;
        std::shared_ptr<std::string> double_header;
        std::shared_ptr<std::string> gameday_type;
        std::shared_ptr<std::string> tiebreaker;
        std::shared_ptr<std::string> calendar_event_id;
        std::shared_ptr<std::string> season_display;
        std::shared_ptr<std::string> day_night;
        std::shared_ptr<int64_t> scheduled_innings;
        std::shared_ptr<bool> reverse_home_away_status;
        std::shared_ptr<int64_t> inning_break_length;
        std::shared_ptr<int64_t> games_in_series;
        std::shared_ptr<int64_t> series_game_number;
        std::shared_ptr<std::string> series_description;
        std::shared_ptr<std::string> record_source;
        std::shared_ptr<std::string> if_necessary;
        std::shared_ptr<std::string> if_necessary_description;
        std::shared_ptr<std::string> reschedule_date;
    };

    struct Date {
        std::shared_ptr<std::string> date;
        std::shared_ptr<int64_t> total_items;
        std::shared_ptr<int64_t> total_events;
        std::shared_ptr<int64_t> total_games;
        std::shared_ptr<int64_t> total_games_in_progress;
        std::shared_ptr<std::vector<Game>> games;
        std::shared_ptr<std::vector<nlohmann::json>> events;
    };

    struct StatsApi {
        std::shared_ptr<std::string> copyright;
        std::shared_ptr<int64_t> total_items;
        std::shared_ptr<int64_t> total_events;
        std::shared_ptr<int64_t> total_games;
        std::shared_ptr<int64_t> total_games_in_progress;
        std::shared_ptr<std::vector<Date>> dates;
    };
}

namespace nlohmann {
    void from_json(const json & j, quicktype::Contributor & x);
    void to_json(json & j, const quicktype::Contributor & x);

    void from_json(const json & j, quicktype::Cut & x);
    void to_json(json & j, const quicktype::Cut & x);

    void from_json(const json & j, quicktype::Image & x);
    void to_json(json & j, const quicktype::Image & x);

    void from_json(const json & j, quicktype::KeywordsAll & x);
    void to_json(json & j, const quicktype::KeywordsAll & x);

    void from_json(const json & j, quicktype::Playback & x);
    void to_json(json & j, const quicktype::Playback & x);

    void from_json(const json & j, quicktype::MlbMedia & x);
    void to_json(json & j, const quicktype::MlbMedia & x);

    void from_json(const json & j, quicktype::Mlb & x);
    void to_json(json & j, const quicktype::Mlb & x);

    void from_json(const json & j, quicktype::Recap & x);
    void to_json(json & j, const quicktype::Recap & x);

    void from_json(const json & j, quicktype::Editorial & x);
    void to_json(json & j, const quicktype::Editorial & x);

    void from_json(const json & j, quicktype::GameNotes & x);
    void to_json(json & j, const quicktype::GameNotes & x);

    void from_json(const json & j, quicktype::ContentMedia & x);
    void to_json(json & j, const quicktype::ContentMedia & x);

    void from_json(const json & j, quicktype::Content & x);
    void to_json(json & j, const quicktype::Content & x);

    void from_json(const json & j, quicktype::Loser & x);
    void to_json(json & j, const quicktype::Loser & x);

    void from_json(const json & j, quicktype::Decisions & x);
    void to_json(json & j, const quicktype::Decisions & x);

    void from_json(const json & j, quicktype::Status & x);
    void to_json(json & j, const quicktype::Status & x);

    void from_json(const json & j, quicktype::LeagueRecord & x);
    void to_json(json & j, const quicktype::LeagueRecord & x);

    void from_json(const json & j, quicktype::Venue & x);
    void to_json(json & j, const quicktype::Venue & x);

    void from_json(const json & j, quicktype::Away & x);
    void to_json(json & j, const quicktype::Away & x);

    void from_json(const json & j, quicktype::Teams & x);
    void to_json(json & j, const quicktype::Teams & x);

    void from_json(const json & j, quicktype::Game & x);
    void to_json(json & j, const quicktype::Game & x);

    void from_json(const json & j, quicktype::Date & x);
    void to_json(json & j, const quicktype::Date & x);

    void from_json(const json & j, quicktype::StatsApi & x);
    void to_json(json & j, const quicktype::StatsApi & x);

    void from_json(const json & j, quicktype::AspectRatio & x);
    void to_json(json & j, const quicktype::AspectRatio & x);

    void from_json(const json & j, quicktype::Type & x);
    void to_json(json & j, const quicktype::Type & x);

    void from_json(const json & j, quicktype::Name & x);
    void to_json(json & j, const quicktype::Name & x);

    inline void from_json(const json & j, quicktype::Contributor& x) {
        x.name = quicktype::get_optional<std::string>(j, "name");
        x.tagline = quicktype::get_optional<std::string>(j, "tagline");
    }

    inline void to_json(json & j, const quicktype::Contributor & x) {
        j = json::object();
        j["name"] = x.name;
        j["tagline"] = x.tagline;
    }

    inline void from_json(const json & j, quicktype::Cut& x) {
        x.aspect_ratio = quicktype::get_optional<quicktype::AspectRatio>(j, "aspectRatio");
        x.width = quicktype::get_optional<int64_t>(j, "width");
        x.height = quicktype::get_optional<int64_t>(j, "height");
        x.src = quicktype::get_optional<std::string>(j, "src");
        x.at2_x = quicktype::get_optional<std::string>(j, "at2x");
        x.at3_x = quicktype::get_optional<std::string>(j, "at3x");
    }

    inline void to_json(json & j, const quicktype::Cut & x) {
        j = json::object();
        j["aspectRatio"] = x.aspect_ratio;
        j["width"] = x.width;
        j["height"] = x.height;
        j["src"] = x.src;
        j["at2x"] = x.at2_x;
        j["at3x"] = x.at3_x;
    }

    inline void from_json(const json & j, quicktype::Image& x) {
        x.title = quicktype::get_optional<std::string>(j, "title");
        x.alt_text = quicktype::get_optional<std::string>(j, "altText");
        x.cuts = quicktype::get_optional<std::vector<quicktype::Cut>>(j, "cuts");
    }

    inline void to_json(json & j, const quicktype::Image & x) {
        j = json::object();
        j["title"] = x.title;
        j["altText"] = x.alt_text;
        j["cuts"] = x.cuts;
    }

    inline void from_json(const json & j, quicktype::KeywordsAll& x) {
        x.type = quicktype::get_optional<quicktype::Type>(j, "type");
        x.value = quicktype::get_optional<std::string>(j, "value");
        x.display_name = quicktype::get_optional<std::string>(j, "displayName");
    }

    inline void to_json(json & j, const quicktype::KeywordsAll & x) {
        j = json::object();
        j["type"] = x.type;
        j["value"] = x.value;
        j["displayName"] = x.display_name;
    }

    inline void from_json(const json & j, quicktype::Playback& x) {
        x.name = quicktype::get_optional<quicktype::Name>(j, "name");
        x.url = quicktype::get_optional<std::string>(j, "url");
        x.width = quicktype::get_optional<std::string>(j, "width");
        x.height = quicktype::get_optional<std::string>(j, "height");
    }

    inline void to_json(json & j, const quicktype::Playback & x) {
        j = json::object();
        j["name"] = x.name;
        j["url"] = x.url;
        j["width"] = x.width;
        j["height"] = x.height;
    }

    inline void from_json(const json & j, quicktype::MlbMedia& x) {
        x.type = quicktype::get_optional<std::string>(j, "type");
        x.state = quicktype::get_optional<std::string>(j, "state");
        x.date = quicktype::get_optional<std::string>(j, "date");
        x.id = quicktype::get_optional<std::string>(j, "id");
        x.headline = quicktype::get_optional<std::string>(j, "headline");
        x.seo_title = quicktype::get_optional<std::string>(j, "seoTitle");
        x.slug = quicktype::get_optional<std::string>(j, "slug");
        x.blurb = quicktype::get_optional<std::string>(j, "blurb");
        x.keywords_all = quicktype::get_optional<std::vector<quicktype::KeywordsAll>>(j, "keywordsAll");
        x.keywords_display = quicktype::get_optional<std::vector<json>>(j, "keywordsDisplay");
        x.image = quicktype::get_optional<quicktype::Image>(j, "image");
        x.no_index = quicktype::get_optional<bool>(j, "noIndex");
        x.media_playback_id = quicktype::get_optional<std::string>(j, "mediaPlaybackId");
        x.title = quicktype::get_optional<std::string>(j, "title");
        x.description = quicktype::get_optional<std::string>(j, "description");
        x.duration = quicktype::get_optional<std::string>(j, "duration");
        x.media_playback_url = quicktype::get_optional<std::string>(j, "mediaPlaybackUrl");
        x.playbacks = quicktype::get_optional<std::vector<quicktype::Playback>>(j, "playbacks");
        x.cclocation_vtt = quicktype::get_optional<std::string>(j, "cclocationVtt");
        x.guid = quicktype::get_optional<std::string>(j, "guid");
    }

    inline void to_json(json & j, const quicktype::MlbMedia & x) {
        j = json::object();
        j["type"] = x.type;
        j["state"] = x.state;
        j["date"] = x.date;
        j["id"] = x.id;
        j["headline"] = x.headline;
        j["seoTitle"] = x.seo_title;
        j["slug"] = x.slug;
        j["blurb"] = x.blurb;
        j["keywordsAll"] = x.keywords_all;
        j["keywordsDisplay"] = x.keywords_display;
        j["image"] = x.image;
        j["noIndex"] = x.no_index;
        j["mediaPlaybackId"] = x.media_playback_id;
        j["title"] = x.title;
        j["description"] = x.description;
        j["duration"] = x.duration;
        j["mediaPlaybackUrl"] = x.media_playback_url;
        j["playbacks"] = x.playbacks;
        j["cclocationVtt"] = x.cclocation_vtt;
        j["guid"] = x.guid;
    }

    inline void from_json(const json & j, quicktype::Mlb& x) {
        x.type = quicktype::get_optional<std::string>(j, "type");
        x.state = quicktype::get_optional<std::string>(j, "state");
        x.date = quicktype::get_optional<std::string>(j, "date");
        x.headline = quicktype::get_optional<std::string>(j, "headline");
        x.seo_title = quicktype::get_optional<std::string>(j, "seoTitle");
        x.slug = quicktype::get_optional<std::string>(j, "slug");
        x.blurb = quicktype::get_optional<std::string>(j, "blurb");
        x.keywords_all = quicktype::get_optional<std::vector<quicktype::KeywordsAll>>(j, "keywordsAll");
        x.keywords_display = quicktype::get_optional<std::vector<json>>(j, "keywordsDisplay");
        x.image = quicktype::get_optional<quicktype::Image>(j, "image");
        x.seo_keywords = quicktype::get_optional<std::string>(j, "seoKeywords");
        x.body = quicktype::get_optional<std::string>(j, "body");
        x.contributors = quicktype::get_optional<std::vector<quicktype::Contributor>>(j, "contributors");
        x.photo = quicktype::get_optional<quicktype::Image>(j, "photo");
        x.url = quicktype::get_optional<std::string>(j, "url");
        x.media = quicktype::get_optional<quicktype::MlbMedia>(j, "media");
        x.subhead = quicktype::get_optional<std::string>(j, "subhead");
    }

    inline void to_json(json & j, const quicktype::Mlb & x) {
        j = json::object();
        j["type"] = x.type;
        j["state"] = x.state;
        j["date"] = x.date;
        j["headline"] = x.headline;
        j["seoTitle"] = x.seo_title;
        j["slug"] = x.slug;
        j["blurb"] = x.blurb;
        j["keywordsAll"] = x.keywords_all;
        j["keywordsDisplay"] = x.keywords_display;
        j["image"] = x.image;
        j["seoKeywords"] = x.seo_keywords;
        j["body"] = x.body;
        j["contributors"] = x.contributors;
        j["photo"] = x.photo;
        j["url"] = x.url;
        j["media"] = x.media;
        j["subhead"] = x.subhead;
    }

    inline void from_json(const json & j, quicktype::Recap& x) {
        x.mlb = quicktype::get_optional<quicktype::Mlb>(j, "mlb");
    }

    inline void to_json(json & j, const quicktype::Recap & x) {
        j = json::object();
        j["mlb"] = x.mlb;
    }

    inline void from_json(const json & j, quicktype::Editorial& x) {
        x.recap = quicktype::get_optional<quicktype::Recap>(j, "recap");
    }

    inline void to_json(json & j, const quicktype::Editorial & x) {
        j = json::object();
        j["recap"] = x.recap;
    }

    inline void from_json(const json & j, quicktype::GameNotes& x) {
    }

    inline void to_json(json & j, const quicktype::GameNotes & x) {
        j = json::object();
    }

    inline void from_json(const json & j, quicktype::ContentMedia& x) {
        x.free_game = quicktype::get_optional<bool>(j, "freeGame");
        x.enhanced_game = quicktype::get_optional<bool>(j, "enhancedGame");
    }

    inline void to_json(json & j, const quicktype::ContentMedia & x) {
        j = json::object();
        j["freeGame"] = x.free_game;
        j["enhancedGame"] = x.enhanced_game;
    }

    inline void from_json(const json & j, quicktype::Content& x) {
        x.link = quicktype::get_optional<std::string>(j, "link");
        x.editorial = quicktype::get_optional<quicktype::Editorial>(j, "editorial");
        x.media = quicktype::get_optional<quicktype::ContentMedia>(j, "media");
        x.highlights = quicktype::get_optional<quicktype::GameNotes>(j, "highlights");
        x.summary = quicktype::get_optional<quicktype::GameNotes>(j, "summary");
        x.game_notes = quicktype::get_optional<quicktype::GameNotes>(j, "gameNotes");
    }

    inline void to_json(json & j, const quicktype::Content & x) {
        j = json::object();
        j["link"] = x.link;
        j["editorial"] = x.editorial;
        j["media"] = x.media;
        j["highlights"] = x.highlights;
        j["summary"] = x.summary;
        j["gameNotes"] = x.game_notes;
    }

    inline void from_json(const json & j, quicktype::Loser& x) {
        x.id = quicktype::get_optional<int64_t>(j, "id");
        x.full_name = quicktype::get_optional<std::string>(j, "fullName");
        x.link = quicktype::get_optional<std::string>(j, "link");
    }

    inline void to_json(json & j, const quicktype::Loser & x) {
        j = json::object();
        j["id"] = x.id;
        j["fullName"] = x.full_name;
        j["link"] = x.link;
    }

    inline void from_json(const json & j, quicktype::Decisions& x) {
        x.winner = quicktype::get_optional<quicktype::Loser>(j, "winner");
        x.loser = quicktype::get_optional<quicktype::Loser>(j, "loser");
        x.save = quicktype::get_optional<quicktype::Loser>(j, "save");
    }

    inline void to_json(json & j, const quicktype::Decisions & x) {
        j = json::object();
        j["winner"] = x.winner;
        j["loser"] = x.loser;
        j["save"] = x.save;
    }

    inline void from_json(const json & j, quicktype::Status& x) {
        x.abstract_game_state = quicktype::get_optional<std::string>(j, "abstractGameState");
        x.coded_game_state = quicktype::get_optional<std::string>(j, "codedGameState");
        x.detailed_state = quicktype::get_optional<std::string>(j, "detailedState");
        x.status_code = quicktype::get_optional<std::string>(j, "statusCode");
        x.abstract_game_code = quicktype::get_optional<std::string>(j, "abstractGameCode");
        x.reason = quicktype::get_optional<std::string>(j, "reason");
    }

    inline void to_json(json & j, const quicktype::Status & x) {
        j = json::object();
        j["abstractGameState"] = x.abstract_game_state;
        j["codedGameState"] = x.coded_game_state;
        j["detailedState"] = x.detailed_state;
        j["statusCode"] = x.status_code;
        j["abstractGameCode"] = x.abstract_game_code;
        j["reason"] = x.reason;
    }

    inline void from_json(const json & j, quicktype::LeagueRecord& x) {
        x.wins = quicktype::get_optional<int64_t>(j, "wins");
        x.losses = quicktype::get_optional<int64_t>(j, "losses");
        x.pct = quicktype::get_optional<std::string>(j, "pct");
    }

    inline void to_json(json & j, const quicktype::LeagueRecord & x) {
        j = json::object();
        j["wins"] = x.wins;
        j["losses"] = x.losses;
        j["pct"] = x.pct;
    }

    inline void from_json(const json & j, quicktype::Venue& x) {
        x.id = quicktype::get_optional<int64_t>(j, "id");
        x.name = quicktype::get_optional<std::string>(j, "name");
        x.link = quicktype::get_optional<std::string>(j, "link");
    }

    inline void to_json(json & j, const quicktype::Venue & x) {
        j = json::object();
        j["id"] = x.id;
        j["name"] = x.name;
        j["link"] = x.link;
    }

    inline void from_json(const json & j, quicktype::Away& x) {
        x.league_record = quicktype::get_optional<quicktype::LeagueRecord>(j, "leagueRecord");
        x.score = quicktype::get_optional<int64_t>(j, "score");
        x.team = quicktype::get_optional<quicktype::Venue>(j, "team");
        x.is_winner = quicktype::get_optional<bool>(j, "isWinner");
        x.split_squad = quicktype::get_optional<bool>(j, "splitSquad");
        x.series_number = quicktype::get_optional<int64_t>(j, "seriesNumber");
    }

    inline void to_json(json & j, const quicktype::Away & x) {
        j = json::object();
        j["leagueRecord"] = x.league_record;
        j["score"] = x.score;
        j["team"] = x.team;
        j["isWinner"] = x.is_winner;
        j["splitSquad"] = x.split_squad;
        j["seriesNumber"] = x.series_number;
    }

    inline void from_json(const json & j, quicktype::Teams& x) {
        x.away = quicktype::get_optional<quicktype::Away>(j, "away");
        x.home = quicktype::get_optional<quicktype::Away>(j, "home");
    }

    inline void to_json(json & j, const quicktype::Teams & x) {
        j = json::object();
        j["away"] = x.away;
        j["home"] = x.home;
    }

    inline void from_json(const json & j, quicktype::Game& x) {
        x.game_pk = quicktype::get_optional<int64_t>(j, "gamePk");
        x.link = quicktype::get_optional<std::string>(j, "link");
        x.game_type = quicktype::get_optional<std::string>(j, "gameType");
        x.season = quicktype::get_optional<std::string>(j, "season");
        x.game_date = quicktype::get_optional<std::string>(j, "gameDate");
        x.official_date = quicktype::get_optional<std::string>(j, "officialDate");
        x.status = quicktype::get_optional<quicktype::Status>(j, "status");
        x.teams = quicktype::get_optional<quicktype::Teams>(j, "teams");
        x.decisions = quicktype::get_optional<quicktype::Decisions>(j, "decisions");
        x.venue = quicktype::get_optional<quicktype::Venue>(j, "venue");
        x.content = quicktype::get_optional<quicktype::Content>(j, "content");
        x.is_tie = quicktype::get_optional<bool>(j, "isTie");
        x.game_number = quicktype::get_optional<int64_t>(j, "gameNumber");
        x.public_facing = quicktype::get_optional<bool>(j, "publicFacing");
        x.double_header = quicktype::get_optional<std::string>(j, "doubleHeader");
        x.gameday_type = quicktype::get_optional<std::string>(j, "gamedayType");
        x.tiebreaker = quicktype::get_optional<std::string>(j, "tiebreaker");
        x.calendar_event_id = quicktype::get_optional<std::string>(j, "calendarEventID");
        x.season_display = quicktype::get_optional<std::string>(j, "seasonDisplay");
        x.day_night = quicktype::get_optional<std::string>(j, "dayNight");
        x.scheduled_innings = quicktype::get_optional<int64_t>(j, "scheduledInnings");
        x.reverse_home_away_status = quicktype::get_optional<bool>(j, "reverseHomeAwayStatus");
        x.inning_break_length = quicktype::get_optional<int64_t>(j, "inningBreakLength");
        x.games_in_series = quicktype::get_optional<int64_t>(j, "gamesInSeries");
        x.series_game_number = quicktype::get_optional<int64_t>(j, "seriesGameNumber");
        x.series_description = quicktype::get_optional<std::string>(j, "seriesDescription");
        x.record_source = quicktype::get_optional<std::string>(j, "recordSource");
        x.if_necessary = quicktype::get_optional<std::string>(j, "ifNecessary");
        x.if_necessary_description = quicktype::get_optional<std::string>(j, "ifNecessaryDescription");
        x.reschedule_date = quicktype::get_optional<std::string>(j, "rescheduleDate");
    }

    inline void to_json(json & j, const quicktype::Game & x) {
        j = json::object();
        j["gamePk"] = x.game_pk;
        j["link"] = x.link;
        j["gameType"] = x.game_type;
        j["season"] = x.season;
        j["gameDate"] = x.game_date;
        j["officialDate"] = x.official_date;
        j["status"] = x.status;
        j["teams"] = x.teams;
        j["decisions"] = x.decisions;
        j["venue"] = x.venue;
        j["content"] = x.content;
        j["isTie"] = x.is_tie;
        j["gameNumber"] = x.game_number;
        j["publicFacing"] = x.public_facing;
        j["doubleHeader"] = x.double_header;
        j["gamedayType"] = x.gameday_type;
        j["tiebreaker"] = x.tiebreaker;
        j["calendarEventID"] = x.calendar_event_id;
        j["seasonDisplay"] = x.season_display;
        j["dayNight"] = x.day_night;
        j["scheduledInnings"] = x.scheduled_innings;
        j["reverseHomeAwayStatus"] = x.reverse_home_away_status;
        j["inningBreakLength"] = x.inning_break_length;
        j["gamesInSeries"] = x.games_in_series;
        j["seriesGameNumber"] = x.series_game_number;
        j["seriesDescription"] = x.series_description;
        j["recordSource"] = x.record_source;
        j["ifNecessary"] = x.if_necessary;
        j["ifNecessaryDescription"] = x.if_necessary_description;
        j["rescheduleDate"] = x.reschedule_date;
    }

    inline void from_json(const json & j, quicktype::Date& x) {
        x.date = quicktype::get_optional<std::string>(j, "date");
        x.total_items = quicktype::get_optional<int64_t>(j, "totalItems");
        x.total_events = quicktype::get_optional<int64_t>(j, "totalEvents");
        x.total_games = quicktype::get_optional<int64_t>(j, "totalGames");
        x.total_games_in_progress = quicktype::get_optional<int64_t>(j, "totalGamesInProgress");
        x.games = quicktype::get_optional<std::vector<quicktype::Game>>(j, "games");
        x.events = quicktype::get_optional<std::vector<json>>(j, "events");
    }

    inline void to_json(json & j, const quicktype::Date & x) {
        j = json::object();
        j["date"] = x.date;
        j["totalItems"] = x.total_items;
        j["totalEvents"] = x.total_events;
        j["totalGames"] = x.total_games;
        j["totalGamesInProgress"] = x.total_games_in_progress;
        j["games"] = x.games;
        j["events"] = x.events;
    }

    inline void from_json(const json & j, quicktype::StatsApi& x) {
        x.copyright = quicktype::get_optional<std::string>(j, "copyright");
        x.total_items = quicktype::get_optional<int64_t>(j, "totalItems");
        x.total_events = quicktype::get_optional<int64_t>(j, "totalEvents");
        x.total_games = quicktype::get_optional<int64_t>(j, "totalGames");
        x.total_games_in_progress = quicktype::get_optional<int64_t>(j, "totalGamesInProgress");
        x.dates = quicktype::get_optional<std::vector<quicktype::Date>>(j, "dates");
    }

    inline void to_json(json & j, const quicktype::StatsApi & x) {
        j = json::object();
        j["copyright"] = x.copyright;
        j["totalItems"] = x.total_items;
        j["totalEvents"] = x.total_events;
        j["totalGames"] = x.total_games;
        j["totalGamesInProgress"] = x.total_games_in_progress;
        j["dates"] = x.dates;
    }

    inline void from_json(const json & j, quicktype::AspectRatio & x) {
        if (j == "16:9") x = quicktype::AspectRatio::THE_169;
        else if (j == "4:3") x = quicktype::AspectRatio::THE_43;
        else if (j == "64:27") x = quicktype::AspectRatio::THE_6427;
        else throw "Input JSON does not conform to schema";
    }

    inline void to_json(json & j, const quicktype::AspectRatio & x) {
        switch (x) {
            case quicktype::AspectRatio::THE_169: j = "16:9"; break;
            case quicktype::AspectRatio::THE_43: j = "4:3"; break;
            case quicktype::AspectRatio::THE_6427: j = "64:27"; break;
            default: throw "This should not happen";
        }
    }

    inline void from_json(const json & j, quicktype::Type & x) {
        if (j == "bodyParagraphCount") x = quicktype::Type::BODY_PARAGRAPH_COUNT;
        else if (j == "customentity.contributor") x = quicktype::Type::CUSTOMENTITY_CONTRIBUTOR;
        else if (j == "game") x = quicktype::Type::GAME;
        else if (j == "game_pk") x = quicktype::Type::GAME_PK;
        else if (j == "player") x = quicktype::Type::PLAYER;
        else if (j == "player_id") x = quicktype::Type::PLAYER_ID;
        else if (j == "season") x = quicktype::Type::SEASON;
        else if (j == "taxonomy") x = quicktype::Type::TAXONOMY;
        else if (j == "team") x = quicktype::Type::TEAM;
        else if (j == "team_id") x = quicktype::Type::TEAM_ID;
        else throw "Input JSON does not conform to schema";
    }

    inline void to_json(json & j, const quicktype::Type & x) {
        switch (x) {
            case quicktype::Type::BODY_PARAGRAPH_COUNT: j = "bodyParagraphCount"; break;
            case quicktype::Type::CUSTOMENTITY_CONTRIBUTOR: j = "customentity.contributor"; break;
            case quicktype::Type::GAME: j = "game"; break;
            case quicktype::Type::GAME_PK: j = "game_pk"; break;
            case quicktype::Type::PLAYER: j = "player"; break;
            case quicktype::Type::PLAYER_ID: j = "player_id"; break;
            case quicktype::Type::SEASON: j = "season"; break;
            case quicktype::Type::TAXONOMY: j = "taxonomy"; break;
            case quicktype::Type::TEAM: j = "team"; break;
            case quicktype::Type::TEAM_ID: j = "team_id"; break;
            default: throw "This should not happen";
        }
    }

    inline void from_json(const json & j, quicktype::Name & x) {
        if (j == "highBit") x = quicktype::Name::HIGH_BIT;
        else if (j == "hlsCloud") x = quicktype::Name::HLS_CLOUD;
        else if (j == "HTTP_CLOUD_WIRED") x = quicktype::Name::HTTP_CLOUD_WIRED;
        else if (j == "HTTP_CLOUD_WIRED_60") x = quicktype::Name::HTTP_CLOUD_WIRED_60;
        else if (j == "mp4Avc") x = quicktype::Name::MP4_AVC;
        else throw "Input JSON does not conform to schema";
    }

    inline void to_json(json & j, const quicktype::Name & x) {
        switch (x) {
            case quicktype::Name::HIGH_BIT: j = "highBit"; break;
            case quicktype::Name::HLS_CLOUD: j = "hlsCloud"; break;
            case quicktype::Name::HTTP_CLOUD_WIRED: j = "HTTP_CLOUD_WIRED"; break;
            case quicktype::Name::HTTP_CLOUD_WIRED_60: j = "HTTP_CLOUD_WIRED_60"; break;
            case quicktype::Name::MP4_AVC: j = "mp4Avc"; break;
            default: throw "This should not happen";
        }
    }
}
