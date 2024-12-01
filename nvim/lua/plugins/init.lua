return {
  {
    "stevearc/conform.nvim",
    -- event = 'BufWritePre', -- uncomment for format on save
    config = function()
      require "configs.conform"
    end,
  },

  {
    "neovim/nvim-lspconfig",
    config = function()
      require("nvchad.configs.lspconfig").defaults()
      require "configs.lspconfig"
    end,
  },

  {
      'postfen/clipboard-image.nvim',
      lazy = false,
      config = function ()
          require "configs.clipboard-image"
      end
  },

  {
  	"williamboman/mason.nvim",
  	opts = {
            ensure_installed = {
                "lua-language-server", "stylua",
                "html-lsp", "css-lsp" , "prettier",
                "python-lsp-server",
                "intelephense",
                "clangd",
                "gopls",
                "tsserver",
                "rust-analyzer",
            },
        },
    },

    {
      'lervag/vimtex',
      lazy = false,
      config = function ()
          require "configs.vimtex"
      end
  },

  {
      'andweeb/presence.nvim',
      lazy = false,
      config = function ()
          require "configs.presence"
      end
  },

  {
      "iamcco/markdown-preview.nvim",
      cmd = { "MarkdownPreviewToggle", "MarkdownPreview", "MarkdownPreviewStop" },
      ft = { "markdown" },
      build = function() vim.fn["mkdp#util#install"]() end,
  },

  {
      "github/copilot.vim",
      lazy = false,
      config = function ()
          require "configs.copilot"
      end
  },
  --
  -- {
  -- 	"nvim-treesitter/nvim-treesitter",
  -- 	opts = {
  -- 		ensure_installed = {
  -- 			"vim", "lua", "vimdoc",
  --      "html", "css"
  -- 		},
  -- 	},
  -- },
}
