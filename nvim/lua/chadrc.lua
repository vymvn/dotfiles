-- This file needs to have same structure as nvconfig.lua
-- https://github.com/NvChad/ui/blob/v3.0/lua/nvconfig.lua
-- Please read that file to know all available options :(

---@type ChadrcConfig
local M = {}

M.ui = {

  theme_toggle = nil,

  statusline = {
    theme = "minimal", -- default/vscode/vscode_colored/minimal

    -- default/round/block/arrow (separators work only for "default" statusline theme;
    -- round and block will work for the minimal theme only)
    separator_style = "block",
    overriden_modules = nil,
  },
}

M.base46 = {
  theme = "decay",
  transparency = true,

  hl_override = {

    Comment = { italic = true },
    ["@comment"] = { italic = true },
  },
}

return M
