-- This file  needs to have same structure as nvconfig.lua 
-- https://github.com/NvChad/NvChad/blob/v2.5/lua/nvconfig.lua

---@type ChadrcConfig
local M = {}

M.ui = {
    theme = 'yoru',
    transparency = true,
    theme_toggle = nil,

    -- hl_override = require "highlights",

    statusline = {
        theme = "default", -- default/vscode/vscode_colored/minimal

        -- default/round/block/arrow (separators work only for "default" statusline theme;
        -- round and block will work for the minimal theme only)
        separator_style = "round",
        -- overriden_modules = nil,
    },

    nvdash = {
        load_on_startup = true
    },

    -- tabufline = {
    --     overriden_modules = function(modules)
    --         modules[4] = (function()
    --             return ""
    --         end)()
    --
    --         -- or table.remove(modules, 4)
    --     end,
    -- },

}

return M
