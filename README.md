# Kill My Idea

**AI-powered startup idea validator that tells founders what's wrong with their idea before the market does.**

Kill My Idea is a full-stack SaaS web application that helps founders turn messy early idea thinking into a structured decision. Instead of encouragement, fragmented research, or generic AI answers, the product asks clarifying questions, analyzes observable market signals, and produces a blunt recommendation with evidence and next steps.

> **Product personality:** Harsh but constructive. The experience should feel like a ruthless investor combined with a sharp cofounder. It must never feel like false encouragement software.

---

## Table of Contents

- [What This Product Does](#what-this-product-does)
- [Who It's For](#who-its-for)
- [What It Must NOT Do](#what-it-must-not-do)
- [Tech Stack](#tech-stack)
- [Architecture Overview](#architecture-overview)
- [Project Structure](#project-structure)
- [The 7-Step Analysis Pipeline](#the-7-step-analysis-pipeline)
  - [Step 1: Interpret](#step-1-interpret)
  - [Step 2: Clarify](#step-2-clarify)
  - [Vagueness Gate](#vagueness-gate)
  - [Step 3: Collect Signals](#step-3-collect-signals)
  - [Step 4: Interpret Signals](#step-4-interpret-signals)
  - [Step 5: Score](#step-5-score)
  - [Step 6: Verdict](#step-6-verdict)
  - [Step 7: Report](#step-7-report)
- [Scoring System Deep Dive](#scoring-system-deep-dive)
  - [The 7 Dimensions](#the-7-dimensions)
  - [Confidence-Weighted Scoring Formula](#confidence-weighted-scoring-formula)
  - [Category-Aware Weight Adjustments](#category-aware-weight-adjustments)
  - [Verdict Thresholds](#verdict-thresholds)
  - [The 7 Guardrail Override Rules](#the-7-guardrail-override-rules)
- [Signal Providers](#signal-providers)
  - [Provider Architecture](#provider-architecture)
  - [HackerNews Provider](#hackernews-provider)
  - [Serper.dev Provider](#serperdev-provider)
  - [Google Trends Provider](#google-trends-provider)
  - [LLM Knowledge Provider](#llm-knowledge-provider)
  - [Evidence Quantifier](#evidence-quantifier)
  - [Graceful Degradation](#graceful-degradation)
- [Database Schema](#database-schema)
  - [Tables Overview](#tables-overview)
  - [Table Details](#table-details)
  - [Enums and Constraints](#enums-and-constraints)
  - [Database Functions](#database-functions)
  - [Migrations](#migrations)
- [API Reference](#api-reference)
  - [Quick Roast](#quick-roast-api)
  - [Ideas](#ideas-api)
  - [Pipeline](#pipeline-api)
  - [Credits & Billing](#credits--billing-api)
  - [Share](#share-api)
  - [Compare](#compare-api)
  - [Admin](#admin-api)
  - [Error Format](#error-format)
  - [Rate Limiting](#rate-limiting)
- [Frontend Architecture](#frontend-architecture)
  - [Route Map](#route-map)
  - [Layout Groups](#layout-groups)
  - [Component Organization](#component-organization)
  - [The Report Page](#the-report-page)
  - [Design Tokens](#design-tokens)
- [Auth System](#auth-system)
  - [Roles and Plans](#roles-and-plans)
  - [Auth Flow](#auth-flow)
  - [Middleware Protection](#middleware-protection)
- [Credit & Payment System](#credit--payment-system)
  - [Credit Mechanics](#credit-mechanics)
  - [Stripe Integration](#stripe-integration)
  - [Credit Packages](#credit-packages)
- [Quick Roast Feature](#quick-roast-feature)
- [Local Development Setup](#local-development-setup)
  - [Prerequisites](#prerequisites)
  - [Step-by-Step Setup](#step-by-step-setup)
  - [Environment Variables](#environment-variables)
  - [Running the App](#running-the-app)
- [Testing](#testing)
- [Deployment](#deployment)
  - [Vercel Setup](#vercel-setup)
  - [CI/CD Pipeline](#cicd-pipeline)
- [Key Architectural Decisions](#key-architectural-decisions)
- [Project Status & Roadmap](#project-status--roadmap)

---

## What This Product Does

Kill My Idea takes a founder's raw startup idea and runs it through a structured analysis pipeline that:

1. **Interprets** the raw idea into a structured summary with assumptions and vagueness detection
2. **Asks clarification questions** targeting weak areas (demand, distribution, competition, etc.)
3. **Collects real market signals** from HackerNews, Google Search, Google Trends, and LLM analysis
4. **Scores the idea** across 7 dimensions using evidence-backed, category-aware scoring
5. **Delivers a verdict** (Pursue / Refine / Test First / Drop / Insufficient Data) with logic guardrails
6. **Generates a full report** with reasoning, assumptions, red/green flags, evidence, and next steps

The product also offers a **Quick Roast** feature — a free, instant, no-signup reaction to an idea that serves as the top-of-funnel acquisition hook.

### Core User Journeys

**Journey A — Quick Roast to Deep Analysis:**
A visitor lands on the homepage, pastes a rough idea, gets a blunt 3-section teaser (first impression, biggest flaw, what to clarify), then signs up for the full evidence-backed analysis.

**Journey B — Serious Evaluation:**
A registered user submits an idea with context (target user, problem statement), answers clarification questions, waits through a 7-step pipeline with real-time progress tracking, and receives a full verdict report.

**Journey C — Compare and Prioritize:**
A repeat user with multiple ideas compares 2-4 of them side-by-side across all dimensions, with an AI-generated takeaway highlighting which to pursue and why.

---

## Who It's For

| Segment | Why They Use It | Likelihood to Pay |
|---------|----------------|-------------------|
| **First-time technical founder** | Needs a structured way to judge whether an idea is worth pursuing | Medium |
| **Indie hacker / repeat builder** | Compares multiple ideas, wants faster decisions | High |
| **Working professional with side project** | Wants to avoid wasting nights and weekends on weak ideas | High |
| **Casual idea explorer** | Mostly seeks entertainment or reassurance | Low |

---

## What It Must NOT Do

These are hard constraints from the PRD (Section 6). Violating any of these breaks product trust:

1. **It must not pretend to predict startup success with certainty.** It's a decision support system, not an oracle.
2. **It must not issue polished verdicts for vague ideas without forcing clarification first.** The vagueness gate enforces this.
3. **It must not become a full founder operating system in v1.** Scope is strictly idea validation.
4. **It must not hide weak evidence behind confident language.** If signals are thin, the product must say so.

---

## Tech Stack

Every technology choice is driven by a **zero-budget constraint** — all services must have free tiers sufficient for development and early launch.

| Layer | Technology | Why This Choice |
|-------|-----------|-----------------|
| **Framework** | Next.js 16.2 (App Router, TypeScript) | Full-stack React framework with SSR, API routes, edge middleware. App Router enables server components and streaming. |
| **Styling** | Tailwind CSS v4 + shadcn/ui v4 | Tailwind v4 uses CSS-based configuration (no `tailwind.config.ts`). shadcn/ui v4 uses `@base-ui/react` instead of Radix — there is no `asChild` prop. |
| **Database** | Supabase PostgreSQL | Free tier: 500MB storage, 50K monthly active users for auth. Includes RLS (Row Level Security), real-time subscriptions, and built-in auth. |
| **Auth** | Supabase Auth | Email + Google OAuth. Sessions managed via cookies with middleware refresh. |
| **Primary LLM** | Google Gemini (Flash 2.0 + 2.5 Flash Preview) | Free tier: 15 RPM. Flash 2.0 for fast tasks (Steps 1, 2). 2.5 Flash Preview for deep reasoning (Steps 4, 7). All calls have 30s timeout + Zod schema validation. |
| **Fallback LLM** | Groq (Llama 3.3 70B Versatile) | Free tier: 30 RPM. Automatic fallback when Gemini fails or is rate-limited. |
| **Web Search** | Serper.dev | Free tier: 2,500 queries/month. Returns real Google search results. ~3 queries per analysis. |
| **Trends** | SerpAPI (Google Trends) | Free tier: 100 queries/month. 1 query per analysis for demand timing. |
| **Community Signals** | HackerNews Algolia API | Completely free, no auth, no rate limit. 4 targeted searches per analysis. |
| **Payments** | Stripe | Test mode for development. INR pricing. Credit-based system. |
| **Email** | Resend | Free tier: 100 emails/day. Used for analysis completion notifications. |
| **Error Monitoring** | Sentry (@sentry/nextjs) | Error tracking in client, server, and edge runtimes. |
| **Analytics** | Vercel Analytics | Page view tracking and conversion events. |
| **Hosting** | Vercel | Free tier with 10-second function timeout. Edge network CDN. |

### Why Not Other Choices?

- **Why not OpenAI?** — No free tier. Gemini Flash is free and good enough. Steps 4 and 7 use the stronger 2.5 Flash Preview model for deeper reasoning.
- **Why not Redis for rate limiting?** — Requires a separate service. DB-backed rate limiting works on serverless and survives cold starts.
- **Why not background jobs (BullMQ, Inngest)?** — Requires a queue server. Client-driven sequential pipeline keeps each step under Vercel's 10s limit and provides natural progress tracking.
- **Why not Reddit for community signals?** — Reddit API requires paid access since 2023. HackerNews Algolia is completely free.

---

## Architecture Overview

### How the System Works (High-Level Data Flow)

```
Visitor lands on homepage
        │
        ▼
   Quick Roast (free, no auth)
   ┌──────────────────────────┐
   │ Paste idea → Gemini 2.0 Flash │
   │ → 3-section teaser        │
   │ → "Sign up for full"      │
   └──────────────────────────┘
        │
        ▼ (signs up, gets 3 free credits)
        │
   Full Analysis Pipeline (1 credit)
   ┌──────────────────────────────────────────────┐
   │ Step 1: Interpret idea (Gemini 2.0 Flash)          │
   │ Step 2: Generate clarification Qs (Gemini)     │
   │    ── Vagueness Gate (blocks if score ≥ 0.7) ──│
   │ Step 3: Collect signals (HN + Serper + Trends) │
   │ Step 4: Interpret signals (Gemini 2.5 Flash Preview)│
   │ Step 5: Score dimensions (deterministic math)  │
   │ Step 6: Determine verdict (deterministic logic) │
   │ Step 7: Generate report (Gemini 2.5 Flash Preview)  │
   └──────────────────────────────────────────────┘
        │
        ▼
   Full Report Page
   ┌──────────────────────────────────────┐
   │ Verdict banner + score + confidence   │
   │ 7 dimension scores with reasoning     │
   │ Assumptions (stated vs inferred)      │
   │ Red flags / Green flags               │
   │ Evidence explorer (by source)         │
   │ Next steps (prioritized actions)      │
   │ Share link / PDF export / Re-analyze  │
   └──────────────────────────────────────┘
```

### Client-Driven Sequential Pipeline (DEC-009)

This is the most important architectural decision. Instead of running the pipeline as a background job:

- **The browser orchestrates all 7 steps** as sequential HTTP requests
- Each step is a separate API call (`POST /api/pipeline/interpret`, `POST /api/pipeline/signals`, etc.)
- Each step stays under Vercel's **10-second function timeout**
- The progress page polls the analysis status and shows real-time step completion
- If a step fails, the client can retry from that specific step (not start over)

**Why this works better than background jobs:**
1. No queue infrastructure needed (zero cost)
2. Natural progress tracking — each API response updates the UI
3. User interaction mid-pipeline — the vagueness gate can pause for user clarification between steps 2 and 3
4. Each step is independently testable and debuggable
5. Stays within Vercel's serverless constraints

### Pipeline Reliability

Every pipeline step includes the following safeguards:

- **Zod schema validation** on all LLM responses (`src/lib/pipeline/schemas.ts`). Malformed JSON or missing fields throw descriptive errors instead of propagating garbage.
- **30-second timeouts** on all LLM calls (Gemini + Groq). **10-second timeouts** on all signal provider API calls (HN, Serper, Trends).
- **Automatic fallback**: Gemini → Groq with exponential backoff retry (up to 3 attempts before fallback).
- **Ownership verification** on all 7 pipeline routes — a user cannot operate on another user's analysis run (returns 403).
- **Graceful degradation**: If any signal provider fails, the pipeline continues with available signals. Only total LLM failure crashes the pipeline.
- **Completed steps tracking**: Each step marks itself complete in `analysis_runs.completed_steps[]`. On retry, the client resumes from the failed step.

---

## Project Structure

```
src/
├── app/                          # Next.js App Router
│   ├── (marketing)/              # Public pages (landing, pricing)
│   │   ├── page.tsx              #   Homepage with Quick Roast
│   │   └── pricing/page.tsx      #   Credit packages
│   ├── (auth)/                   # Auth pages (no sidebar)
│   │   ├── signin/page.tsx
│   │   ├── signup/page.tsx
│   │   ├── forgot-password/page.tsx
│   │   └── reset-password/page.tsx
│   ├── (app)/                    # Authenticated app (sidebar + navbar)
│   │   ├── dashboard/page.tsx    #   Ideas list, stats, credit balance
│   │   ├── ideas/
│   │   │   ├── new/page.tsx      #   Multi-step idea submission wizard
│   │   │   └── [ideaId]/
│   │   │       ├── page.tsx      #   Idea detail with versions
│   │   │       ├── clarify/page.tsx   # Answer clarification questions
│   │   │       └── report/[runId]/
│   │   │           ├── page.tsx       # Full analysis report
│   │   │           └── progress/page.tsx  # Real-time pipeline progress
│   │   ├── compare/page.tsx      #   Compare 2-4 ideas side-by-side
│   │   └── settings/
│   │       ├── page.tsx          #   Profile settings
│   │       └── billing/page.tsx  #   Credits, packages, transactions
│   ├── (admin)/                  # Admin panel (admin sidebar)
│   │   ├── admin/page.tsx        #   Admin dashboard metrics
│   │   ├── admin/analytics/page.tsx
│   │   ├── admin/jobs/page.tsx   #   Analysis runs, retry failed
│   │   ├── admin/users/page.tsx  #   User management
│   │   ├── admin/moderation/page.tsx
│   │   └── admin/prompts/page.tsx
│   ├── api/                      # API routes (32 endpoints)
│   │   ├── quick-roast/route.ts
│   │   ├── ideas/route.ts
│   │   ├── ideas/[id]/
│   │   │   ├── route.ts
│   │   │   ├── analyze/route.ts
│   │   │   ├── clarify/route.ts
│   │   │   └── report/route.ts
│   │   ├── pipeline/
│   │   │   ├── interpret/route.ts
│   │   │   ├── clarify/route.ts
│   │   │   ├── signals/route.ts
│   │   │   ├── interpret-signals/route.ts
│   │   │   ├── score/route.ts
│   │   │   ├── verdict/route.ts
│   │   │   └── report/route.ts
│   │   ├── credits/
│   │   │   ├── balance/route.ts
│   │   │   ├── purchase/route.ts
│   │   │   ├── transactions/route.ts
│   │   │   └── verify/route.ts
│   │   ├── share/route.ts
│   │   ├── share/[slug]/route.ts
│   │   ├── ideas/compare/route.ts
│   │   ├── admin/...
│   │   ├── webhooks/stripe/route.ts
│   │   ├── feedback/route.ts
│   │   └── user/profile/route.ts
│   ├── auth/callback/route.ts    # OAuth callback handler
│   ├── layout.tsx                # Root layout (providers, fonts)
│   ├── error.tsx                 # Global error boundary
│   ├── not-found.tsx             # 404 page
│   ├── robots.ts                 # SEO robots.txt
│   └── sitemap.ts                # SEO sitemap
│
├── components/
│   ├── ui/                       # shadcn/ui primitives (24 components)
│   │   ├── alert.tsx, animated-group.tsx, avatar.tsx, badge.tsx,
│   │   │   button.tsx, card.tsx, checkbox.tsx, dialog.tsx,
│   │   │   dropdown-menu.tsx, input.tsx, label.tsx, popover.tsx,
│   │   │   progress.tsx, scroll-area.tsx, select.tsx, separator.tsx,
│   │   │   sheet.tsx, skeleton.tsx, sonner.tsx, switch.tsx,
│   │   │   table.tsx, tabs.tsx, textarea.tsx, tooltip.tsx
│   │   └── ...
│   ├── layout/                   # App shells
│   │   ├── marketing-navbar.tsx
│   │   ├── app-navbar.tsx
│   │   ├── app-sidebar.tsx
│   │   ├── admin-sidebar.tsx
│   │   └── footer.tsx
│   ├── marketing/                # Landing page components
│   │   ├── hero-section-new.tsx
│   │   ├── how-it-works.tsx
│   │   ├── pricing-preview.tsx
│   │   └── quick-roast-form.tsx
│   ├── report/                   # Report page components (14 files)
│   │   ├── verdict-banner.tsx        # Verdict + score + confidence
│   │   ├── pursue-warning.tsx        # Warning layer for "Pursue" verdicts
│   │   ├── sub-score-grid.tsx        # 7 dimension score cards
│   │   ├── reasoning-section.tsx     # Per-dimension narrative + evidence
│   │   ├── assumptions-panel.tsx     # User-stated vs inferred
│   │   ├── flags-list.tsx            # Red flags + green flags
│   │   ├── evidence-badge.tsx        # Verified/unverified badge
│   │   ├── evidence-explorer.tsx     # Tabbed evidence browser by source
│   │   ├── clarification-answers.tsx # Q&A pairs from clarification
│   │   ├── next-steps-panel.tsx      # Prioritized action items
│   │   ├── share-export-bar.tsx      # Share link + PDF + re-analyze
│   │   ├── feedback-button.tsx       # Flag inaccurate/unhelpful analysis
│   │   ├── report-preview.tsx        # Skeleton preview (teaser mode)
│   │   ├── paywall-overlay.tsx       # Blurred overlay for free users
│   │   └── pdf/
│   │       ├── report-pdf-document.tsx
│   │       └── pdf-export-button.tsx
│   ├── dashboard/
│   │   ├── welcome-banner.tsx
│   │   ├── ideas-list.tsx
│   │   └── credit-balance-card.tsx
│   ├── compare/
│   │   ├── idea-selector.tsx
│   │   ├── comparison-table.tsx
│   │   └── comparison-takeaway.tsx
│   ├── billing/
│   │   ├── credit-packages.tsx
│   │   └── transaction-history.tsx
│   ├── auth/
│   │   ├── signin-form.tsx
│   │   ├── signup-form.tsx
│   │   └── forgot-password-form.tsx
│   ├── admin/
│   │   ├── metrics-grid.tsx
│   │   ├── job-table.tsx
│   │   ├── user-table.tsx
│   │   ├── moderation-queue.tsx
│   │   └── prompt-editor.tsx
│   └── analysis/
│       └── vagueness-blocker.tsx
│
├── lib/
│   ├── pipeline/                 # Core analysis engine
│   │   ├── steps/
│   │   │   ├── 01-interpret.ts   # Step 1: Raw → structured summary
│   │   │   ├── 02-clarify.ts     # Step 2: Generate questions
│   │   │   ├── 03-collect-signals.ts  # Step 3: All providers in parallel
│   │   │   ├── 04-interpret-signals.ts # Step 4: Signals → dimension insights
│   │   │   ├── 05-score.ts       # Step 5: Weighted scoring (deterministic)
│   │   │   ├── 06-verdict.ts     # Step 6: Verdict + overrides (deterministic)
│   │   │   └── 07-report.ts      # Step 7: Full report generation
│   │   ├── ai/
│   │   │   ├── gemini-client.ts  # Google Gemini API wrapper
│   │   │   ├── groq-client.ts    # Groq (Llama 3.3) API wrapper
│   │   │   ├── retry.ts          # Retry with exponential backoff + Groq fallback
│   │   │   └── rate-limiter.ts   # DB-backed rate limiting
│   │   ├── scoring/
│   │   │   ├── weighted-scorer.ts    # Main scoring algorithm
│   │   │   ├── evidence-quantifier.ts # Signal → baseline computation
│   │   │   ├── logic-overrides.ts    # 7 verdict guardrail rules
│   │   │   ├── category-weights.ts   # Per-category weight adjustments
│   │   │   └── source-affinity.ts    # Confidence boost for signal diversity
│   │   ├── signals/
│   │   │   ├── provider-registry.ts  # Central registry of all providers
│   │   │   ├── hackernews.ts         # HackerNews Algolia API
│   │   │   ├── serper.ts             # Serper.dev Google Search
│   │   │   ├── google-trends.ts      # SerpAPI Google Trends
│   │   │   ├── llm-knowledge.ts      # LLM market/competitor analysis
│   │   │   └── types.ts              # SignalProvider interface
│   │   ├── ml/
│   │   │   └── categorizer.ts        # Idea category classifier
│   │   ├── orchestrator.ts           # Pipeline status management
│   │   ├── vagueness-gate.ts         # Blocks pipeline if idea too vague
│   │   ├── category-preservation.ts  # Reuses category across reruns
│   │   ├── schemas.ts                # Zod schemas for LLM response validation
│   │   ├── ownership.ts              # Pipeline route ownership verification
│   ├── auth/
│   │   ├── provider.tsx          # AuthProvider React context
│   │   └── hooks.ts              # useAuth(), useProfile() hooks
│   ├── supabase/
│   │   ├── client.ts             # Browser Supabase client
│   │   ├── server.ts             # Server Supabase clients (admin + user)
│   │   └── middleware.ts         # Supabase middleware for token refresh
│   ├── email/
│   │   ├── client.ts             # Resend client
│   │   ├── send.ts               # Fire-and-forget email sender
│   │   └── templates/
│   │       └── analysis-complete.tsx  # Analysis done email template
│   ├── utils/
│   │   ├── validators.ts         # Zod schemas for all API inputs
│   │   ├── sanitize.ts           # HTML strip, XSS prevention
│   │   ├── formatters.ts         # Date/number formatting
│   │   └── rate-limit-helper.ts  # User rate limit check wrapper
│   ├── constants.ts              # All scoring weights, thresholds, limits
│   ├── logger.ts                 # Structured logging (Sentry)
│   ├── analytics.ts              # Vercel Analytics events
│   └── hooks/                    # Custom React hooks
│
├── types/
│   ├── database.ts               # All DB enums, row types, JSONB shapes
│   ├── pipeline.ts               # Pipeline step input/output types
│   └── api.ts                    # API request/response types
│
├── __tests__/                    # Vitest unit tests
│   └── lib/
│       ├── pipeline/
│       │   ├── evidence-quantifier.test.ts
│       │   └── vagueness-gate.test.ts
│       ├── scoring/
│       │   └── weighted-scorer.test.ts
│       └── utils/
│           ├── sanitize.test.ts
│           └── validators.test.ts
│
├── middleware.ts                  # Next.js edge middleware (auth + route protection)
└── instrumentation.ts            # Sentry server instrumentation

supabase/
└── migrations/
    ├── 001_initial_schema.sql           # 10 tables
    ├── 002_tier1_signal_sources.sql     # Signal source constraints
    ├── 003_tier2_error_recovery.sql     # completed_steps for retry
    ├── 004_tier2_email_notifications.sql # Email preferences
    ├── 005_tier3_indexes.sql            # Performance indexes
    └── 006_tier4_feedback.sql           # Feedback table + RLS
```

---

## The 7-Step Analysis Pipeline

This is the heart of the product. Understanding how this pipeline works is essential to understanding Kill My Idea.

### How It's Orchestrated

The pipeline is **client-driven and sequential**. The browser sends 7 HTTP requests, one after another:

```
Browser                          Server                          Database
  │                                │                                │
  │── POST /api/pipeline/interpret ──▶ Gemini 2.0 Flash ──▶ structured_summary
  │◀── { interpretation, category } ─│                               │
  │                                │                                │
  │── POST /api/pipeline/clarify ────▶ Gemini 2.0 Flash ──▶ questions[]
  │◀── { questions: [...] } ────────│                               │
  │                                │                                │
  │  ┌─ VAGUENESS GATE ─────────────────────────────────────────────┐
  │  │ If vagueness_score ≥ 0.7:                                    │
  │  │   Pipeline PAUSES. User redirected to /clarify page.         │
  │  │   User answers questions. Pipeline resumes on submit.        │
  │  └──────────────────────────────────────────────────────────────┘
  │                                │                                │
  │── POST /api/pipeline/signals ───▶ [HN, Serper, Trends, LLM]    │
  │◀── { signals[], sources_used } ─│     (all in parallel)         │
  │                                │                                │
  │── POST /api/pipeline/interpret-signals ▶ Gemini 2.5 Flash Preview   │
  │◀── { dimension_insights[] } ────│                               │
  │                                │                                │
  │── POST /api/pipeline/score ─────▶ Pure math (no LLM)           │
  │◀── { scores{}, overall_score } ─│                               │
  │                                │                                │
  │── POST /api/pipeline/verdict ───▶ Pure logic (no LLM)          │
  │◀── { verdict, override_reason } │                               │
  │                                │                                │
  │── POST /api/pipeline/report ────▶ Gemini 2.5 Flash Preview         │
  │◀── { report: ReportContent } ───│                               │
  │                                │                                │
  │── Redirect to /report/[runId] ──│                               │
```

Each step updates the `analysis_runs` table with the current status and `completed_steps[]` array. The progress page polls this status to show real-time feedback to the user.

### Pipeline Status Flow

```
queued → interpreting → clarifying → waiting_for_clarification (optional)
       → collecting_signals → interpreting_signals → scoring
       → generating_verdict → generating_report → completed
                                                 ↘ failed (at any point)
```

---

### Step 1: Interpret

**File:** `src/lib/pipeline/steps/01-interpret.ts`

**Purpose:** Transform the founder's raw text input into a structured summary that the rest of the pipeline can work with.

**Input:**
```typescript
{
  raw_input: string,      // "An app that helps dog owners find vets nearby"
  target_user?: string,   // "Dog owners in urban areas"
  problem_statement?: string  // "Hard to find quality vets at short notice"
}
```

**What happens:**
1. Sends the raw input to Gemini 2.0 Flash with a structured extraction prompt
2. Gemini returns a JSON object with: problem, solution, target_user, business_model, key_assumptions, vagueness_flags, vagueness_score
3. Also runs ML categorization to classify the idea into one of 10 categories (b2b_saas, consumer_app, devtool, marketplace, hardware, fintech, edtech, healthtech, creator_economy, other)

**The exact system prompt:**
```
You are a startup idea analyst. Given a raw idea description, extract a structured summary.

Respond with valid JSON matching this exact shape:
{
  "problem": "The core problem being solved (1-2 sentences)",
  "solution": "The proposed solution (1-2 sentences)",
  "target_user": "Who this is for (specific persona or segment)",
  "business_model": "How this would make money (or 'unclear' if not stated)",
  "key_assumptions": ["assumption 1", "assumption 2", ...],
  "vagueness_flags": ["vague area 1", ...],
  "vagueness_score": 0.0
}

Rules:
- "key_assumptions" should list 2-5 core assumptions the idea relies on
- "vagueness_flags" should list areas where the input is unclear or underspecified
- "vagueness_score" is 0.0 (crystal clear) to 1.0 (extremely vague)
- If target_user or problem is not explicitly stated, infer the most likely answer
  and add a vagueness_flag
- Be analytical, not cheerful. Do not add optimism.
```

**LLM Config:** Gemini 2.0 Flash, temperature 0.4, max tokens 1,024

**Output stored in:** `analysis_runs.input_snapshot.interpretation` and `analysis_runs.input_snapshot.category`

---

### Step 2: Clarify

**File:** `src/lib/pipeline/steps/02-clarify.ts`

**Purpose:** Generate 3-6 targeted clarification questions that probe the weakest or most vague areas of the idea.

**What happens:**
1. Takes the structured summary from Step 1
2. Sends it to Gemini 2.0 Flash with a question generation prompt
3. Each question targets one of the 7 scoring dimensions
4. Creates an `idea_version` record with these questions

**The exact system prompt:**
```
You are a startup idea analyst preparing clarification questions. Based on the
structured interpretation of a startup idea, generate targeted questions that
would help validate or refute the idea.

Respond with valid JSON matching this shape:
{
  "questions": [
    {
      "id": "q1",
      "question": "The question text",
      "dimension": "demand",
      "why_asked": "Brief explanation of why this matters"
    }
  ]
}

Rules:
- Generate 3-6 questions, no more, no less
- Each question must target one of these dimensions: ${SCORING_DIMENSIONS.join(', ')}
  (resolves to: demand, urgency, distribution, differentiation, competition, monetization, execution)
- Prioritize questions about the weakest or most vague areas
- Questions should be specific and answerable, not generic
- "id" must be sequential: q1, q2, q3, etc.
- "why_asked" should be 1 sentence explaining what this question helps validate
- Do NOT ask obvious questions the founder already answered
- Focus on: demand evidence, distribution strategy, competitive landscape,
  monetization clarity, execution risk
```

**LLM Config:** Gemini 2.0 Flash, temperature 0.5, max tokens 1,024

**Output stored in:** `idea_versions.clarification_questions`

---

### Vagueness Gate

**File:** `src/lib/pipeline/vagueness-gate.ts`

**Purpose:** Prevent the pipeline from producing low-quality analysis on under-specified ideas.

**How it works:**
- After Step 2 (Clarify), the vagueness score from Step 1 is checked
- If `vagueness_score >= 0.7`, the pipeline **stops**
- The user is redirected to the clarification page where they must answer the questions
- The pipeline only resumes after the user submits their answers
- The UI shows a `VaguenessBlocker` component explaining why the pipeline paused

**Why 0.7?** This threshold was chosen to block clearly underspecified ideas (e.g., "I want to build something with AI") while allowing somewhat vague but workable ideas to proceed. It's defined in `src/lib/constants.ts` as `VAGUENESS_BLOCK_THRESHOLD`.

**This implements PRD Section 6, Rule 2:** "It must not issue polished verdicts for vague ideas without forcing clarification first."

---

### Step 3: Collect Signals

**File:** `src/lib/pipeline/steps/03-collect-signals.ts`

**Purpose:** Gather real market evidence from multiple external sources.

**What happens:**
1. Gets all enabled signal providers from the registry
2. Runs **all providers in parallel** using `Promise.allSettled` (graceful degradation)
3. Each provider returns an array of `SignalResult` objects
4. Failed providers are tracked in `sources_failed` but don't crash the pipeline
5. All signals are stored in the `signal_evidence` table

**Providers executed (all in parallel):**
- HackerNews Algolia API — 4 targeted searches
- Serper.dev — 3 Google search queries (if API key present)
- SerpAPI Google Trends — 1 trend query (if API key present)
- LLM Knowledge — Competitor and market analysis via Gemini

**Output:**
```typescript
{
  signals: SignalResult[],      // All collected signals
  sources_used: string[],       // ["hackernews", "serper", "google_trends", "llm_knowledge"]
  sources_failed: string[],     // Any providers that errored out
  signals_collected: number     // Total signal count
}
```

**Each signal stored in `signal_evidence`:**
```typescript
{
  analysis_run_id: string,
  source_type: "hackernews" | "serper" | "google_trends" | "llm_knowledge",
  signal_category: "demand" | "urgency" | "distribution" | ...,
  raw_data: Record<string, unknown>,  // Full raw response from provider
  normalized_summary: string,          // Human-readable summary
  signal_strength: number,             // 0.0-1.0
  source_url: string | null            // Real URL for traceability
}
```

---

### Step 4: Interpret Signals

**File:** `src/lib/pipeline/steps/04-interpret-signals.ts`

**Purpose:** Transform raw signals into scored dimension insights. This is where signals become scores.

**What happens:**
1. **Pre-computes evidence baselines** from countable signal data (HN points, Serper position, Trends growth rate)
2. Sends all signals + founder's clarification answers to Gemini 2.5 Flash Preview (stronger reasoning model)
3. LLM returns signal strength per dimension, but is **constrained within ±0.15 of the baseline**
4. This anchoring prevents wild scoring swings between runs with the same signals

**The Baseline Anchoring System (DEC-020):**

This is critical for reproducibility. Without baselines, the LLM might score the same signals differently on different runs. Here's how it works:

```
Raw signals → Evidence Quantifier → Baselines (0.0-1.0 per dimension)
                                         │
                                    ±0.15 band
                                         │
LLM interpretation ──────────────▶ Clamped signal_strength
```

Example: If HackerNews signals for "demand" compute a baseline of 0.6, the LLM can only return a signal_strength between 0.45 and 0.75 for that dimension.

**Output per dimension:**
```typescript
{
  dimension: "demand",
  signal_strength: 0.65,     // 0.0-1.0, clamped to ±0.15 of baseline
  confidence: 0.7,           // How much evidence exists
  summary: "Multiple HN discussions about this problem space...",
  evidence_count: 4,
  evidence_urls: ["https://news.ycombinator.com/..."]
}
```

---

### Step 5: Score

**File:** `src/lib/pipeline/steps/05-score.ts`

**Purpose:** Calculate the final weighted scores per dimension and the overall score. This step is **pure deterministic math — no LLM involved.**

**What happens:**
1. Takes the 7 dimension insights from Step 4
2. Converts signal_strength (0-1) to a score (0-10) scale
3. Applies category-specific weight adjustments
4. Applies confidence weighting (low-confidence dimensions have less impact)
5. Blends confidence-weighted average (70%) with simple-weighted average (30%)

See [Scoring System Deep Dive](#scoring-system-deep-dive) for the full math.

**Output:**
```typescript
{
  scores: {
    demand: { score: 7.2, weight: 0.20, confidence: 0.8 },
    urgency: { score: 5.5, weight: 0.20, confidence: 0.6 },
    // ... all 7 dimensions
  },
  overall_score: 6.3  // 0-10 weighted average
}
```

---

### Step 6: Verdict

**File:** `src/lib/pipeline/steps/06-verdict.ts`

**Purpose:** Determine the final verdict using score thresholds and logic overrides. This step is **pure deterministic logic — no LLM involved.**

**What happens:**
1. Maps overall_score to a raw verdict using thresholds:
   - `7.5+` → Pursue
   - `5.5 - 7.49` → Refine
   - `4.0 - 5.49` → Test First
   - `0 - 3.99` → Drop
2. Runs 7 guardrail override rules that can upgrade or downgrade the verdict
3. Returns the final verdict with any override explanation

See [The 7 Guardrail Override Rules](#the-7-guardrail-override-rules) for full details.

**Output:**
```typescript
{
  verdict: "refine",
  raw_verdict: "pursue",              // Before override
  override_applied: true,
  override_reason: "Overall score is high but distribution channel is unclear.",
  confidence: 0.65
}
```

---

### Step 7: Report

**File:** `src/lib/pipeline/steps/07-report.ts`

**Purpose:** Generate the comprehensive human-readable report that the user sees.

**What happens:**
1. Compiles all data: scores, verdict, signals, assumptions, clarification Q&A
2. Sends everything to Gemini 2.5 Flash Preview with strict formatting rules
3. LLM generates: executive summary, dimension reasoning, assumptions (user-stated vs inferred), red/green flags, next steps, weaknesses, and strengthening suggestions
4. **Evidence verification (DEC-022):** All evidence_refs must use real URLs from collected signals. LLM-generated claims without real URLs must be prefixed with `[Unverified]`.

**LLM Config:** Gemini 2.5 Flash Preview, temperature 0.5, max tokens 4,096

**Full report structure:**
```typescript
interface ReportContent {
  executive_summary: string;
  idea_interpretation: {
    problem: string;
    solution: string;
    target_user: string;
  };
  verdict: {
    verdict: Verdict;
    score: number;
    confidence: number;
    one_liner: string;  // One punchy, memorable sentence
  };
  dimension_reasoning: Array<{
    dimension: string;
    score: number;
    reasoning: string;       // Detailed explanation with evidence
    evidence_refs: string[]; // Real URLs or "[Unverified] ..." claims
  }>;
  assumptions: Array<{
    text: string;
    type: "user_stated" | "inferred";
    source: string;
  }>;
  red_flags: Array<{
    text: string;
    severity: "high" | "medium" | "low";
    evidence_ref: string;
  }>;
  green_flags: Array<{
    text: string;
    strength: "strong" | "moderate";
    evidence_ref: string;
  }>;
  next_steps: Array<{
    action: string;
    priority: number;
    type: "test" | "refine" | "validate" | "build";
  }>;
  weaknesses: string;
  strengthening_suggestions: string;
}
```

---

## Scoring System Deep Dive

### The 7 Dimensions

Every idea is scored across 7 dimensions. These are defined in `src/lib/constants.ts`:

| Dimension | Weight | What It Measures |
|-----------|--------|-----------------|
| **Demand** | 20% | Evidence that people care or search for this problem area |
| **Urgency** | 20% | How painful or frequent the problem appears to be |
| **Distribution** | 20% | Whether the founder can realistically reach users |
| **Differentiation** | 12% | Whether the product angle is sufficiently distinct |
| **Competition** | 10% | How hard the existing market may be to enter |
| **Monetization** | 10% | Whether pricing or willingness to pay appears plausible |
| **Execution** | 8% | How hard it may be to build, launch, and sustain |

**Why these weights?** Demand, urgency, and distribution are weighted highest (20% each) because ideas most commonly fail due to lack of demand, lack of urgency, or inability to reach users. Execution is weighted lowest (8%) because it's useful but secondary to whether anyone wants the product.

### Confidence-Weighted Scoring Formula

**File:** `src/lib/pipeline/scoring/weighted-scorer.ts`

The scoring algorithm blends two approaches to prevent low-confidence dimensions from distorting results:

**Step 1: Score each dimension (0-10)**
```
dimension_score = signal_strength × 10
```

**Step 2: Adjust weights by category**
```
adjusted_weight = clamp(base_weight + category_adjustment, 0, 1)
```
(See Category-Aware Weight Adjustments below)

**Step 3: Compute effective weight per dimension**

This is the key formula. Each dimension's effective weight combines its base weight with its confidence level:
```
effective_weight = adjusted_weight × (0.5 + 0.5 × confidence)
```
This means a dimension with 100% confidence gets its full weight, while a dimension with 0% confidence gets only 50% of its weight. Low-confidence dimensions still have a voice, but a muted one.

**Step 4: Confidence-Weighted Average**
```
confidence_weighted = Σ(score × effective_weight) / Σ(effective_weight)
```

**Step 5: Simple-Weighted Average**
```
simple_weighted = Σ(score × adjusted_weight) / Σ(adjusted_weight)
```
Every dimension contributes equally regardless of confidence.

**Step 6: Blend (70/30)**
```
overall_score = 0.70 × confidence_weighted + 0.30 × simple_weighted
```

**Why 70/30?** Pure confidence-weighted scoring could suppress important dimensions just because signals were thin. The 30% simple-weighted component ensures every dimension has some voice. But the 70% confidence-weighted component means well-evidenced dimensions dominate.

**Missing dimensions** (no signals at all) default to:
- Score: 5.0 (neutral, not pessimistic)
- Confidence: 0.15 (very low — barely affects the weighted score)

### Category-Aware Weight Adjustments

**File:** `src/lib/pipeline/scoring/category-weights.ts`

Different idea categories have different priorities. A B2B SaaS idea cares more about distribution than a hardware idea. Each category can shift dimension weights by up to ±3%:

| Category | Adjustments |
|----------|------------|
| **b2b_saas** | Distribution +3%, Monetization +2%, Urgency -2%, Execution -3% |
| **consumer_app** | Demand +3%, Distribution +2%, Differentiation -2%, Execution -3% |
| **devtool** | Demand -3%, Distribution +3%, Differentiation +2%, Competition -2% |
| **marketplace** | Demand +3%, Distribution +3%, Competition -3%, Execution -3% |
| **hardware** | Execution +3%, Monetization +2%, Distribution -3%, Demand -2% |
| **fintech** | Monetization +3%, Competition +2%, Execution -2%, Demand -3% |
| **edtech** | Demand +3%, Urgency -3%, Monetization +2%, Competition -2% |
| **healthtech** | Urgency +3%, Execution +2%, Distribution -3%, Demand -2% |
| **creator_economy** | Differentiation +3%, Distribution +2%, Monetization -3%, Urgency -2% |
| **other** | No adjustments |

Example: For a B2B SaaS idea, distribution weight goes from 20% to 23%, because for B2B, having a clear channel to reach customers is even more critical.

### Verdict Thresholds

| Overall Score | Verdict | Meaning |
|--------------|---------|---------|
| **7.5 - 10.0** | Pursue | Strong signals across most dimensions. Worth building. |
| **5.5 - 7.49** | Refine | Promise exists but key gaps need addressing first. |
| **4.0 - 5.49** | Test First | Too uncertain for commitment. Run experiments. |
| **0.0 - 3.99** | Drop | Weak signals across the board. Pivot or move on. |
| (Special) | Insufficient Data | Evidence too thin for any responsible recommendation. |

**Important PRD note:** "Test First" is a **valid and positive** outcome, not a disguised rejection. The report should include specific experiments (interviews, landing pages, waitlist tests) the founder should run.

### The 7 Guardrail Override Rules

**File:** `src/lib/pipeline/scoring/logic-overrides.ts`

Raw scores can be misleading. These 7 rules override score-based verdicts when specific signal conditions warrant it. Rules are checked in the priority order shown below — the first matching rule applies.

**Priority order:** Rules 1-3 catch data-quality issues (→ Insufficient Data). Rules 4-5 handle score overrides (→ Refine). Rules 6-7 enforce evidence requirements (→ Test First).

> **Note:** The rule numbering below matches the conceptual grouping. In the code (`logic-overrides.ts`), the Insufficient Data rules (1, 6, 7 below) are checked first, then the score overrides (2, 3), then the evidence rules (4, 5). The first match wins.

**Rule 1: High Score + Unclear Distribution → Downgrade to Refine**
```
Condition: rawVerdict === "pursue" AND distribution.confidence < 0.5
Override:  "pursue" → "refine"
Reason:    "Overall score is high but distribution channel is unclear or unvalidated."
```
*Why:* A high overall score shouldn't mean "pursue" if you have no idea how to reach users. This is the most common over-optimistic failure mode.

**Rule 2: Low Score + Strong Differentiation + Real Demand → Upgrade to Refine**
```
Condition: rawVerdict === "drop"
           AND differentiation.score >= 7
           AND demand.score >= 5
           AND demand.confidence >= 0.5
Override:  "drop" → "refine"
Reason:    "Score is low overall but the idea shows strong differentiation with real demand signals. Worth refining."
```
*Why:* Some ideas score low because of execution difficulty or competitive pressure, but the core insight is genuinely unique and there's real demand. These deserve a second chance.

**Rule 3: 3+ Low-Confidence Dimensions → Insufficient Data**
```
Condition: 3 or more dimensions with confidence < 0.4
Override:  Any verdict → "insufficient_data"
Reason:    "X of 7 dimensions have low confidence. Not enough evidence for a responsible recommendation."
```
*Why:* This is the primary data-quality guardrail. If most dimensions have thin evidence, the product shouldn't pretend to have an opinion. This implements PRD Section 6, Rule 4: "It must not hide weak evidence behind confident language."

**Rule 4: 3+ Conflicting Signals + Pursue → Downgrade to Test First**
```
Condition: rawVerdict === "pursue"
           AND 3+ dimensions with (score >= 7 AND confidence < 0.5)
                                OR (score <= 3 AND confidence < 0.5)
Override:  "pursue" → "test_first"
Reason:    "X dimensions have conflicting or uncertain signals. Test the key assumptions before committing."
```
*Why:* High scores with low confidence mean "looks good but we're not sure." Three or more such dimensions means too much uncertainty for a "pursue" recommendation.

**Rule 5: Zero Demand Evidence → Downgrade to Test First**
```
Condition: (rawVerdict === "pursue" OR rawVerdict === "refine")
           AND demand.confidence < 0.3
Override:  "pursue"/"refine" → "test_first"
Reason:    "No strong evidence of market demand found. Validate demand before investing further."
```
*Why:* Demand is the most critical dimension. Without evidence that anyone actually wants this, even a high-scoring idea should be tested first.

**Rule 6: Too Few External Signals → Insufficient Data**
```
Condition: total_signal_count < 3
Override:  Any verdict → "insufficient_data"
Reason:    "Only N external signals collected (minimum 3 required). Not enough evidence for a responsible recommendation."
```
*Why:* If we collected fewer than 3 total external signals, there simply isn't enough real-world evidence to make any recommendation. This prevents the system from issuing verdicts based primarily on LLM knowledge (which can hallucinate).

**Rule 7: Low Average Confidence → Insufficient Data**
```
Condition: average confidence across all 7 dimensions < 0.35
Override:  Any verdict → "insufficient_data"
Reason:    "Average confidence is below 0.35. Evidence is too thin for a confident verdict."
```
*Why:* Even if no single dimension is terrible, if the AVERAGE confidence across all dimensions is below 0.35, the overall picture is too uncertain for any responsible recommendation.

---

## Signal Providers

### Provider Architecture

**File:** `src/lib/pipeline/signals/types.ts`

All signal providers implement the same interface:

```typescript
interface SignalProvider {
  name: string;                    // "hackernews", "serper", etc.
  collect(input: SignalInput): Promise<SignalResult[]>;
}

interface SignalResult {
  source_type: SignalSourceType;
  signal_category: SignalCategory; // Which dimension this signal relates to
  raw_data: Record<string, unknown>;
  normalized_summary: string;
  signal_strength: number;         // 0.0 - 1.0
  source_url: string | null;
}
```

This modular design means adding a new signal source (e.g., Product Hunt, Crunchbase) only requires:
1. Implement the `SignalProvider` interface
2. Register it in `provider-registry.ts`

No pipeline code changes needed.

### HackerNews Provider

**File:** `src/lib/pipeline/signals/hackernews.ts`

**API:** HackerNews Algolia (free, no auth, no rate limit)

**How it works:**
1. Extracts keywords from the structured summary (problem + solution + target user)
2. Runs **4 parallel searches** against the Algolia API:
   - Problem/pain point discussions → demand signal (`searchHN(problemKw, 'story', 'points>5')`)
   - Solution/product discussions → competition signal (`searchHN(solutionKw, 'story', 'points>5')`)
   - "Show HN" launches → differentiation signal (`searchHN('Show HN ${solutionKw}', 'show_hn')`)
   - "Ask HN" for user needs → urgency signal (`searchHN('Ask HN ${problemKw}', 'ask_hn')`)
3. Each search returns max 8 hits
4. Deduplicates results by `objectID`
5. Filters by engagement: `points > 2 OR num_comments > 1`
6. Max 6 results per signal type, max 20 signals total per analysis
7. Maps each result to a `SignalResult` with:
   - `signal_category` assigned based on search type
   - `signal_strength` based on points and comment count
   - `source_url` pointing to the actual HN thread

**What it captures:** Community interest, pain point discussions, competitor launches ("Show HN"), user needs ("Ask HN"), demand signals in the tech community.

**Limitation:** HackerNews is biased toward tech, developer, and startup audiences. For ideas targeting non-tech markets (e.g., local food delivery), HN signals may be sparse or irrelevant. The category-source affinity system reduces HN's influence for non-tech categories.

### Serper.dev Provider

**File:** `src/lib/pipeline/signals/serper.ts`

**API:** Serper.dev (2,500 free queries/month)

**How it works:**
1. Constructs 3 targeted Google search queries:
   - Problem/demand: `"{problem keywords}" problem solution` (6 results)
   - Competitor landscape: `"{solution keywords}" alternatives competitors` (6 results)
   - Market/monetization: `"{solution keywords}" market size pricing` (6 results)
2. Each query returns up to 6 Google search results
3. Maps results to signals with:
   - `signal_strength` based on result position (position ≤ 3 → 0.7, ≤ 6 → 0.5, else → 0.3) with 40% penalty for keyword-irrelevant results
   - `source_url` pointing to the actual web page
   - `signal_category` assigned based on query type (demand, competition, monetization)
4. Max 15 signals total per analysis

**Budget:** ~3 queries per analysis = ~833 analyses/month on free tier.

**What it captures:** Real-world web presence, competitor landscape, pricing evidence, market size indicators.

### Google Trends Provider

**File:** `src/lib/pipeline/signals/google-trends.ts`

**API:** SerpAPI Google Trends (100 free queries/month)

**How it works:**
1. Constructs a single search term from the core problem/solution
2. Fetches 12-month interest-over-time data from Google Trends
3. Analyzes the trend direction based on growth percentage:
   - `growing` — growth > 20% (further split: >50% growth gets higher signal strength of 0.85)
   - `stable` — growth between -20% and +20%
   - `declining` — growth < -20%
   - `insufficient_data` — fewer than 4 data points in the timeline
4. Maps to signals with:
   - `signal_category: "demand"` (trends primarily indicate demand)
   - `signal_strength` based on trend direction and growth rate

**Budget:** 1 query per analysis = 100 analyses/month on free tier.

**What it captures:** Demand timing — is interest in this problem area growing, shrinking, or stable? This is the only signal that captures temporal dynamics.

### LLM Knowledge Provider

**File:** `src/lib/pipeline/signals/llm-knowledge.ts`

**API:** Gemini 2.0 Flash / Groq Llama 3.3 70B fallback (no additional cost)

**How it works:**
1. Sends the structured idea summary to Gemini 2.0 Flash with **2 separate LLM calls** (validated with Zod schemas) (temperature 0.3):
   - **Call 1 — Competitor analysis** (max 2,048 tokens): "Identify real competitors, market size, and failed startups in this space." Uses a detailed system prompt requiring real company names, real URLs, and honest assessments.
   - **Call 2 — Market validation** (max 1,536 tokens): "Assess real-world market signals for this idea." Analyzes market size, growth potential, demand indicators, and common failure patterns.
2. Parses JSON responses from each call
3. Maps each competitor and market insight to signals

**What it captures:** Competitor landscape, market sizing, pricing intelligence, failure pattern awareness.

**Critical caveat:** LLM-generated data may include hallucinated companies and fake URLs. The evidence verification system (DEC-022) addresses this by:
- Signals from LLM Knowledge with a `source_url` get a baseline strength of 0.5
- Signals without a `source_url` get a lower baseline of 0.35
- In the final report, LLM-based claims without real URLs are prefixed with `[Unverified]`

### Evidence Quantifier

**File:** `src/lib/pipeline/scoring/evidence-quantifier.ts`

This module converts raw signal data into numerical baselines that constrain the LLM's scoring in Step 4.

**How baselines are computed:**

For HackerNews signals (based on HN's engagement distribution — top 1% = >100pts, top 5% = >30pts):
```
points > 100 OR comments > 50   → 0.85
points > 30  OR comments > 15   → 0.65
points > 10  OR comments > 5    → 0.45
else                             → 0.25
```

For Serper signals (Google ranking position + keyword relevance check — 40% penalty for irrelevant results):
```
position ≤ 3          → 0.7
position ≤ 6          → 0.5
else                  → 0.3
```

For Google Trends signals:
```
growing (>50% growth) → 0.85
growing (any)         → 0.65
stable                → 0.45
declining             → 0.25
else                  → 0.35
```

For LLM Knowledge signals (capped below all real sources to prevent hallucination from inflating baselines):
```
with source_url       → 0.4
without source_url    → 0.25
```

Multiple signals for the same dimension use **diminishing returns:**
```
total = signal[0].strength × 1.0
      + signal[1].strength × 0.77  (1 / 1.3)
      + signal[2].strength × 0.63  (1 / 1.6)
      + ...
normalized = total / count
```

A **diversity bonus** of +0.05 is added per additional unique source type (max +0.15 for 4 sources).

Final baseline is clamped to `[0.0, 1.0]`.

### Graceful Degradation

The pipeline is designed to succeed even when signal providers fail:

```
All 4 providers succeed  → Best quality analysis
3 providers succeed      → Good quality, note missing source
2 providers succeed      → Reduced confidence, warn user
1 provider succeeds      → Low confidence, may trigger "Insufficient Data"
0 providers succeed      → Pipeline fails (extremely rare)
```

Each provider runs independently via `Promise.allSettled`. A provider timeout or API error is logged but doesn't crash the pipeline. The scoring system naturally reduces confidence for dimensions with fewer signals.

---

## Database Schema

### Tables Overview

```
profiles ──────────┐
                   │ user_id
ideas ─────────────┤
  │                │
  │ idea_id        │
  ▼                │
idea_versions      │
  │                │
  │ idea_version_id│
  ▼                │
analysis_runs ─────┤
  │                │
  │ analysis_run_id│
  ├────────────────┤
  ▼                │
signal_evidence    │
                   │
reports ───────────┘
  │
  ▼
share_links

credit_transactions (linked to profiles + analysis_runs)
admin_settings (standalone key-value store)
feedback (linked to profiles + analysis_runs, added in migration 006)
```

### Table Details

#### `profiles` — User accounts
Extends Supabase `auth.users`. Created automatically via database trigger on signup.

| Column | Type | Description |
|--------|------|-------------|
| id | uuid (PK) | References auth.users.id |
| email | text | User's email |
| display_name | text | Display name |
| role | text | visitor, registered, paid, admin |
| plan | text | free, starter, pro |
| credit_balance | integer | Current credit count (default: 3 on signup) |
| avatar_url | text | Profile picture URL |
| email_notifications | boolean | Opt-in for email notifications (default: true) |
| created_at | timestamptz | Account creation time |
| updated_at | timestamptz | Last profile update |

#### `ideas` — Startup idea submissions

| Column | Type | Description |
|--------|------|-------------|
| id | uuid (PK) | |
| user_id | uuid (FK → profiles) | Nullable for Quick Roast ideas |
| title | text | Short title (3-200 chars) |
| raw_input | text | Full idea description (10-5000 chars) |
| target_user | text | Who the idea serves (max 500 chars) |
| problem_statement | text | Problem being solved (max 2000 chars) |
| status | text | draft, submitted, analyzing, completed, failed |
| category | text | One of 10 categories (set during analysis) |
| is_quick_roast | boolean | True for Quick Roast-originated ideas |
| tags | text[] | User-defined tags |
| deleted_at | timestamptz | Soft delete timestamp |
| created_at | timestamptz | |
| updated_at | timestamptz | |

#### `idea_versions` — Versioned interpretations per idea

| Column | Type | Description |
|--------|------|-------------|
| id | uuid (PK) | |
| idea_id | uuid (FK → ideas) | |
| version_number | integer | Sequential version |
| structured_summary | jsonb | StructuredSummary from Step 1 |
| clarification_questions | jsonb | ClarificationQuestion[] from Step 2 |
| clarification_answers | jsonb | User's answers (key-value by question ID) |
| clarification_status | text | pending, answered, skipped |
| created_at | timestamptz | |

#### `analysis_runs` — Pipeline execution records

| Column | Type | Description |
|--------|------|-------------|
| id | uuid (PK) | |
| idea_id | uuid (FK → ideas) | |
| idea_version_id | uuid (FK → idea_versions) | |
| status | text | 11-state status enum (see Pipeline Status Flow) |
| current_step | integer | 1-7, which step is executing |
| input_snapshot | jsonb | Frozen copy of all inputs at analysis start |
| scores | jsonb | AnalysisScores from Step 5 |
| overall_score | numeric | 0-10 weighted score |
| verdict | text | pursue, refine, test_first, drop, insufficient_data |
| confidence | numeric | 0-1 overall confidence |
| assumptions | jsonb | Assumption[] from interpretation |
| red_flags | jsonb | RedFlag[] from report |
| green_flags | jsonb | GreenFlag[] from report |
| override_applied | boolean | Whether a guardrail rule overrode the raw verdict |
| override_reason | text | Explanation of the override |
| completed_steps | integer[] | [1, 2, 3, ...] for retry resilience (DEC-024) |
| credits_charged | integer | Credits deducted (usually 1) |
| error | text | Error message if failed |
| started_at | timestamptz | Pipeline start time |
| completed_at | timestamptz | Pipeline completion time |
| created_at | timestamptz | |
| updated_at | timestamptz | |

#### `signal_evidence` — Raw signals from providers

| Column | Type | Description |
|--------|------|-------------|
| id | uuid (PK) | |
| analysis_run_id | uuid (FK → analysis_runs) | |
| source_type | text | hackernews, serper, google_trends, llm_knowledge |
| signal_category | text | demand, urgency, distribution, differentiation, competition, monetization, execution |
| raw_data | jsonb | Full raw response from provider |
| normalized_summary | text | Human-readable signal summary |
| signal_strength | numeric | 0.0-1.0 |
| source_url | text | Real URL for traceability (null for LLM knowledge) |
| created_at | timestamptz | |

#### `reports` — Generated analysis reports

| Column | Type | Description |
|--------|------|-------------|
| id | uuid (PK) | |
| analysis_run_id | uuid (UNIQUE FK → analysis_runs) | One report per run |
| idea_id | uuid (FK → ideas) | |
| report_type | text | "full" or "quick_roast" |
| content | jsonb | ReportContent (full report structure) |
| quick_roast_teaser | jsonb | Quick Roast 3-section teaser |
| created_at | timestamptz | |

#### `share_links` — Public shareable links

| Column | Type | Description |
|--------|------|-------------|
| id | uuid (PK) | |
| report_id | uuid (FK → reports) | |
| slug | text (UNIQUE) | 12-char nanoid for URL |
| visibility | text | public, unlisted |
| view_count | integer | Incremented on each view |
| expires_at | timestamptz | Optional expiration |
| created_at | timestamptz | |

#### `credit_transactions` — Immutable audit log

| Column | Type | Description |
|--------|------|-------------|
| id | uuid (PK) | |
| user_id | uuid (FK → profiles) | |
| type | text | purchase, deduction, refund, adjustment, signup_bonus |
| amount | integer | Positive for credits added, negative for deductions |
| balance_after | integer | Balance after this transaction |
| description | text | Human-readable description |
| analysis_run_id | uuid | For deductions: which analysis used the credit |
| razorpay_order_id | text | Reused for Stripe payment_intent ID |
| razorpay_payment_id | text | Reused for Stripe session ID |
| created_at | timestamptz | |

#### `admin_settings` — Runtime configuration store

| Column | Type | Description |
|--------|------|-------------|
| key | text (PK) | Setting name |
| value | jsonb | Setting value |
| updated_at | timestamptz | |

Default keys: `free_signup_credits` (3), `signal_providers`, `classification_method`, `credit_packages`, `scoring_weights`

#### `feedback` — User feedback on analyses

| Column | Type | Description |
|--------|------|-------------|
| id | uuid (PK) | |
| user_id | uuid (FK → profiles) | |
| analysis_run_id | uuid | Optional: which analysis |
| type | text | inaccurate, unhelpful, other |
| message | text | Free-text feedback |
| created_at | timestamptz | |

### Enums and Constraints

All enums are implemented as CHECK constraints (not PostgreSQL enum types) for flexibility:

```sql
-- Idea status
CHECK (status IN ('draft', 'submitted', 'analyzing', 'completed', 'failed'))

-- Analysis run status (11 states)
CHECK (status IN ('queued', 'interpreting', 'clarifying', 'waiting_for_clarification',
  'collecting_signals', 'interpreting_signals', 'scoring', 'generating_verdict',
  'generating_report', 'completed', 'failed'))

-- Verdicts
CHECK (verdict IN ('pursue', 'refine', 'test_first', 'drop', 'insufficient_data'))

-- Signal sources
CHECK (source_type IN ('hackernews', 'llm_knowledge', 'serper', 'google_trends'))

-- Signal dimensions
CHECK (signal_category IN ('demand', 'urgency', 'distribution', 'differentiation',
  'competition', 'monetization', 'execution'))

-- Idea categories (10-class)
CHECK (category IN ('b2b_saas', 'consumer_app', 'devtool', 'marketplace',
  'hardware', 'fintech', 'edtech', 'healthtech', 'creator_economy', 'other'))
```

### Database Functions

**`deduct_credits(p_user_id, p_amount, p_description, p_analysis_run_id)`**
Atomically deducts credits with row-level locking. Checks balance >= amount before deducting. Creates a `credit_transactions` record.

**`add_credits(p_user_id, p_amount, p_description, p_razorpay_order_id, p_razorpay_payment_id)`**
Atomically adds credits. Creates a `credit_transactions` record. Used for purchases, refunds, and adjustments.

**`handle_new_user()` (trigger)**
Fires on `auth.users` INSERT. Creates a `profiles` row with role='registered', plan='free', credit_balance=3.

**`update_updated_at()` (trigger)**
Fires on UPDATE for all tables with `updated_at` column. Automatically sets `updated_at = now()`.

### Migrations

| File | Purpose |
|------|---------|
| `001_initial_schema.sql` | Creates 9 core tables, functions, triggers, RLS policies |
| `002_tier1_signal_sources.sql` | Adds signal source type constraints for serper and google_trends |
| `003_tier2_error_recovery.sql` | Adds `completed_steps integer[]` to analysis_runs for retry support |
| `004_tier2_email_notifications.sql` | Adds `email_notifications boolean` to profiles |
| `005_tier3_indexes.sql` | Creates 6 performance indexes on frequently queried columns |
| `006_tier4_feedback.sql` | Creates feedback table with RLS policies |

---

## API Reference

### Quick Roast API

#### `POST /api/quick-roast`
**Auth:** None (public)
**Rate Limit:** 3 requests/hour per IP

**Request:**
```json
{
  "idea": "An app that helps dog owners find emergency vets nearby"
}
```

**Response (200):**
```json
{
  "roast": {
    "first_impression": "This is essentially a vet-specific Yelp...",
    "biggest_flaw": "Distribution is your killer. Dog owners already Google...",
    "what_to_clarify": "What makes this better than Google Maps + reviews?"
  },
  "share_slug": "abc123def456"
}
```

---

### Ideas API

#### `POST /api/ideas` — Create idea
**Auth:** Required
**Rate Limit:** 30/min

**Request:**
```json
{
  "title": "VetNow - Emergency Vet Finder",
  "raw_input": "An app that helps dog owners find emergency vets...",
  "target_user": "Dog owners in urban areas",
  "problem_statement": "Hard to find quality vets at short notice"
}
```

#### `GET /api/ideas` — List user's ideas
**Auth:** Required
Returns all non-deleted ideas for the authenticated user.

#### `GET /api/ideas/[id]` — Get idea detail
**Auth:** Required (must own the idea)

#### `PATCH /api/ideas/[id]` — Update idea
**Auth:** Required (must own the idea)

#### `DELETE /api/ideas/[id]` — Soft delete
**Auth:** Required (must own the idea)
Sets `deleted_at` timestamp. Does not permanently delete.

#### `POST /api/ideas/[id]/analyze` — Start analysis
**Auth:** Required
**Cost:** 1 credit
Deducts a credit, creates an `idea_version` and `analysis_run`, and returns the `run_id` for the client to start the pipeline.

#### `POST /api/ideas/[id]/clarify` — Submit clarification answers
**Auth:** Required
Stores answers and resumes the pipeline (marks clarification_status as "answered").

#### `GET /api/ideas/[id]/analysis/[runId]` — Get analysis run status
**Auth:** Required
Returns the current status, completed steps, and progress of an analysis run. Used by the progress page to poll pipeline status in real-time.

#### `GET /api/ideas/[id]/report` — Get report
**Auth:** Required
Returns the full report for a completed analysis run.

---

### Pipeline API

Each endpoint executes one step of the 7-step pipeline. All require authentication and include the `run_id` in the request body.

| Endpoint | Step | LLM Used | Notes |
|----------|------|----------|-------|
| `POST /api/pipeline/interpret` | 1 | Gemini 2.0 Flash | Returns structured summary + category |
| `POST /api/pipeline/clarify` | 2 | Gemini 2.0 Flash | Returns 3-6 clarification questions |
| `POST /api/pipeline/signals` | 3 | None (external APIs) | Runs all providers in parallel |
| `POST /api/pipeline/interpret-signals` | 4 | Gemini 2.5 Flash Preview | Returns dimension insights |
| `POST /api/pipeline/score` | 5 | None (math) | Returns weighted scores |
| `POST /api/pipeline/verdict` | 6 | None (logic) | Returns verdict + overrides |
| `POST /api/pipeline/report` | 7 | Gemini 2.5 Flash Preview | Returns full report |

**Request format (all pipeline endpoints):**
```json
{
  "run_id": "uuid-of-analysis-run",
  "idea_id": "uuid-of-idea"
}
```

---

### Credits & Billing API

#### `GET /api/credits/balance` — Get credit balance
**Auth:** Required

#### `POST /api/credits/purchase` — Create Stripe checkout session
**Auth:** Required
```json
{ "package_id": "pack_5" }  // pack_5, pack_20, or pack_50
```

#### `POST /api/credits/verify` — Verify payment after checkout
**Auth:** Required

#### `GET /api/credits/transactions` — Transaction history
**Auth:** Required

#### `POST /api/webhooks/stripe` — Stripe webhook
**Auth:** Stripe signature verification
Handles `checkout.session.completed` events. Adds credits atomically.

---

### Share API

#### `POST /api/share` — Create share link
**Auth:** Required (must own the report)
```json
{
  "report_id": "uuid",
  "visibility": "unlisted"  // "public" or "unlisted"
}
```

**Response:**
```json
{
  "slug": "abc123def456",
  "url": "https://killmyidea.com/report/abc123def456"
}
```

#### `GET /api/share/[slug]` — View shared report
**Auth:** None (public)
Increments `view_count`.

---

### Compare API

#### `POST /api/ideas/compare` — Compare 2-4 ideas
**Auth:** Required
```json
{
  "idea_ids": ["uuid1", "uuid2", "uuid3"]
}
```
Returns side-by-side scores and an AI-generated comparison takeaway.

---

### Admin API

All admin endpoints require the `admin` role. Non-admin users receive a `403`.

| Endpoint | Purpose |
|----------|---------|
| `GET /api/admin/metrics` | Platform stats (user count, analysis count, verdict distribution) |
| `GET /api/admin/jobs` | List analysis runs with filtering/pagination |
| `POST /api/admin/jobs/[runId]/retry` | Retry a failed analysis from the failed step |
| `GET /api/admin/users` | List/search users with credit balances |
| `POST /api/admin/users/[userId]/credits` | Manually adjust a user's credit balance |
| `GET /api/admin/moderation` | Review flagged content and feedback submissions |
| `GET/PATCH /api/admin/prompts` | View and update system prompts |

---

### Error Format

All API errors follow a consistent format:

```json
{
  "error": "machine_readable_code",
  "message": "Human readable message",
  "details": {}
}
```

Common error codes:
| Code | HTTP Status | Meaning |
|------|-------------|---------|
| `unauthorized` | 401 | Missing or invalid auth token |
| `forbidden` | 403 | Authenticated but insufficient permissions |
| `not_found` | 404 | Resource doesn't exist |
| `validation_error` | 400 | Request body failed Zod validation |
| `rate_limited` | 429 | Too many requests (includes `retryAfter` in seconds) |
| `insufficient_credits` | 402 | Not enough credits for analysis |
| `pipeline_error` | 500 | Analysis step failed |

### Rate Limiting

Rate limits are DB-backed (not in-memory) so they survive serverless cold starts and work across multiple instances.

| Tier | Limit | Applies To |
|------|-------|-----------|
| **Quick Roast** | 3/hour per IP | `POST /api/quick-roast` |
| **Analysis** | 10/hour per user | `POST /api/ideas/[id]/analyze` |
| **Pipeline Steps** | 100/min per user | All `POST /api/pipeline/*` |
| **Idea CRUD** | 30/min per user | `POST/PATCH/DELETE /api/ideas/*` |
| **Credit Payment** | 10/min per user | `POST /api/credits/purchase` |
| **Read** | 60/min per user | All GET endpoints |
| **Write** | 30/min per user | All other POST/PATCH endpoints |
| **Admin** | 30/min per user | All `/api/admin/*` |

---

## Frontend Architecture

### Route Map

**23 total routes** organized into 4 layout groups:

#### Marketing (Public)
| Route | Page | Purpose |
|-------|------|---------|
| `/` | Landing | Hero + Quick Roast form + FAQ |
| `/pricing` | Pricing | Credit packages comparison |
| `/report/[shareId]` | Shared Report | Public full report view |
| `/roast/[shareId]` | Shared Roast | Public quick roast teaser |

#### Auth (No Sidebar)
| Route | Page | Purpose |
|-------|------|---------|
| `/signin` | Sign In | Email + Google OAuth |
| `/signup` | Sign Up | Account creation |
| `/forgot-password` | Password Reset Request | |
| `/reset-password` | New Password | |

#### App (Authenticated, Sidebar)
| Route | Page | Purpose |
|-------|------|---------|
| `/dashboard` | Dashboard | Ideas list, stats, credit balance |
| `/ideas/new` | New Idea | Multi-step submission wizard |
| `/ideas/[ideaId]` | Idea Detail | Versions, analysis history |
| `/ideas/[ideaId]/clarify` | Clarification | Answer pipeline questions |
| `/ideas/[ideaId]/report/[runId]` | **Report** | Full analysis report (core page) |
| `/ideas/[ideaId]/report/[runId]/progress` | Progress | Real-time pipeline tracking |
| `/compare` | Compare | Side-by-side 2-4 ideas |
| `/settings` | Settings | Profile editing |
| `/settings/billing` | Billing | Credits, packages, transactions |

#### Admin (Admin Only)
| Route | Page | Purpose |
|-------|------|---------|
| `/admin` | Dashboard | Platform metrics |
| `/admin/analytics` | Analytics | Conversion tracking |
| `/admin/jobs` | Jobs | Analysis runs, retry failed |
| `/admin/users` | Users | User management, credit adjustments |
| `/admin/moderation` | Moderation | Content and feedback review |
| `/admin/prompts` | Prompts | System prompt editing |

### Layout Groups

Next.js route groups (parenthesized folders) define shared layouts:

```
(marketing)  →  MarketingNavbar + Footer (no sidebar)
(auth)       →  Centered card layout (minimal chrome)
(app)        →  AppNavbar + AppSidebar (full app shell)
(admin)      →  AppNavbar + AdminSidebar (admin shell)
```

### Component Organization

Components are organized by feature, not by type:

```
components/
├── ui/          # Generic primitives (shadcn/ui). Used everywhere.
├── layout/      # App shells. Used in layouts.
├── marketing/   # Landing page. Used only on (marketing) routes.
├── report/      # Report page sections. Used only on report route.
├── dashboard/   # Dashboard widgets. Used on /dashboard.
├── compare/     # Comparison UI. Used on /compare.
├── billing/     # Credit/payment UI. Used on /settings/billing.
├── auth/        # Auth forms. Used on (auth) routes.
├── admin/       # Admin tools. Used on (admin) routes.
└── analysis/    # Pipeline UI. Used during analysis flow.
```

The entire app uses a warm dark theme with glassmorphism cards, soft lavender (`#7c6ce7`/`#9b8ce8`) accents, and a warm color palette. All surfaces use dark backgrounds (`#1a1a1c` base, `#222224` surface) with subtle white-opacity borders for depth.

### The Report Page

The report page (`/ideas/[ideaId]/report/[runId]`) is the most complex and important page. It's composed of 14 components (12 content sections + 2 supporting components):

```
┌─────────────────────────────────────────┐
│           VerdictBanner                  │  Verdict + Score + Confidence
│  ┌─────────────────────────────────┐    │
│  │  PURSUE  │  7.2/10  │  High    │    │
│  └─────────────────────────────────┘    │
│                                         │
│  ⚠ PursueWarning (if verdict=pursue)   │  "Even positive verdicts have unknowns"
├─────────────────────────────────────────┤
│           SubScoreGrid                   │  7 dimension cards + overall confidence
│  ┌──────┐┌──────┐┌──────┐┌──────┐      │
│  │Demand││Urgency│Distribution│Diff.│   │
│  │ 7.2  ││ 5.5  ││   8.1    ││ 6.3│   │
│  └──────┘└──────┘└──────────┘└─────┘   │
├─────────────────────────────────────────┤
│         ReasoningSection                 │  Per-dimension narrative + evidence refs
├─────────────────────────────────────────┤
│         AssumptionsPanel                 │  Blue = user-stated, Amber = inferred
├─────────────────────────────────────────┤
│           FlagsList                      │  Red flags (left) + Green flags (right)
├─────────────────────────────────────────┤
│        EvidenceExplorer                  │  Tabbed by source (HN, Serper, Trends)
├─────────────────────────────────────────┤
│     ClarificationAnswers                 │  Q&A pairs from clarification step
├─────────────────────────────────────────┤
│        NextStepsPanel                    │  3-5 prioritized action items
├─────────────────────────────────────────┤
│        FeedbackButton                    │  Flag inaccurate/unhelpful analysis
├─────────────────────────────────────────┤
│        ShareExportBar                    │  Copy link, PDF export, re-analyze
└─────────────────────────────────────────┘
```

**Layout:** The report page uses a sidebar navigation pattern. A fixed sidebar lists all report sections, allowing quick jumps. The main content area scrolls independently.

**Key UI patterns:**
- **Accordion reasoning sections** — Each dimension's reasoning is collapsible, keeping the page scannable while allowing deep dives.
- **Compact evidence explorer** — Evidence items are displayed in a dense, tabbed layout (by source) with expandable details rather than full-width cards.
- **Founder-friendly language** — All LLM-generated report content uses plain, direct language aimed at founders. No internal scoring jargon (e.g., "demand_signal_strength") is exposed in the report UI. Scores are presented as simple numbers with context.

### Design Tokens

| Token | Value | Usage |
|-------|-------|-------|
| Primary color | `#7c6ce7` (soft lavender) | Headers, primary buttons, accents |
| Pursue | `#22C55E` (green) | Pursue verdict badge |
| Refine | `#F59E0B` (amber) | Refine verdict badge |
| Test First | `#3B82F6` (blue) | Test First verdict badge |
| Drop | `#EF4444` (red) | Drop verdict badge |
| Insufficient Data | `#6B7280` (gray) | Insufficient Data badge |
| Heading font | Inter | All headings and body text |
| Data font | JetBrains Mono | Scores, numbers, data labels |
| Base text size | 14px | Body text |

**Theme:** Warm dark theme applied globally.

| Dark Theme Token | Value | Usage |
|------------------|-------|-------|
| Background | `#1a1a1c` | Page background |
| Surface | `#222224` | Panels, containers |
| Cards | `bg-white/[0.05] border-white/[0.08]` | Glassmorphism card style |
| Accent primary | `#7c6ce7` (soft lavender) | Buttons, links, active states |
| Accent secondary | `#9b8ce8` (lighter lavender) | Hover states, highlights |

---

## Auth System

### Roles and Plans

**4 Roles** (escalating access):

| Role | Access | How Assigned |
|------|--------|-------------|
| `visitor` | Quick Roast only, view shared reports | Before signup |
| `registered` | Save ideas, run analyses, view history | On signup |
| `paid` | Full reports, comparisons, exports, evidence | After first purchase |
| `admin` | All above + admin panel, prompt editing, user management | Manual assignment |

**3 Plans:**

| Plan | Credits | Price |
|------|---------|-------|
| `free` | 3 (signup bonus) | Free |
| `starter` | 5 | ₹99 |
| `pro` | 20 or 50 | ₹299 or ₹599 |

### Auth Flow

1. User signs up via email or Google OAuth (Supabase Auth)
2. `handle_new_user()` trigger creates a `profiles` row with role=registered, credit_balance=3
3. Supabase issues a JWT token stored in HTTP-only cookies
4. Middleware refreshes the token on every request
5. `AuthProvider` context fetches the profile on mount and provides `useAuth()` hook

### Middleware Protection

**File:** `src/middleware.ts`

The Next.js edge middleware runs on every request and handles:

1. **Token refresh:** Refreshes Supabase auth cookies to prevent expiration
2. **Protected routes:** Redirects unauthenticated users from `/dashboard`, `/ideas`, `/compare`, `/settings` to `/signin`
3. **Admin routes:** Redirects non-admin users from `/admin/*` to `/dashboard`
4. **Auth routes:** Redirects already-authenticated users from `/signin`, `/signup` to `/dashboard`

---

## Credit & Payment System

### Credit Mechanics

- **1 credit = 1 full analysis** (7-step pipeline)
- **Quick Roasts are free** (unlimited, rate-limited by IP)
- Credits are deducted **at the start** of the pipeline (before Step 1)
- If the pipeline fails, the credit is still consumed (refund via admin)
- Credit balance is tracked atomically in the `profiles` table via database functions
- Every credit change creates an immutable `credit_transactions` record for auditing

### Stripe Integration

**Payment flow:**

```
User clicks "Buy 5 Credits"
        │
        ▼
POST /api/credits/purchase { package_id: "pack_5" }
        │
        ▼
Server creates Stripe Checkout Session
        │
        ▼
User redirected to Stripe Checkout (hosted page)
        │
        ▼
User completes payment on Stripe
        │
        ▼
Stripe sends webhook → POST /api/webhooks/stripe
        │
        ▼
Server verifies signature, checks idempotency
        │
        ▼
add_credits() function adds credits atomically
        │
        ▼
User redirected back to /settings/billing?success=true
```

**Idempotency:** The webhook handler checks if a `credit_transaction` already exists for the Stripe session ID before adding credits. This prevents double-crediting if Stripe sends the webhook multiple times.

### Credit Packages

| Package | Credits | Price (INR) | Per-Credit Cost |
|---------|---------|------------|-----------------|
| `pack_5` | 5 | ₹99 | ₹19.80 |
| `pack_20` | 20 | ₹299 | ₹14.95 |
| `pack_50` | 50 | ₹599 | ₹11.98 |

**Signup bonus:** 3 free credits on account creation.

---

## Quick Roast Feature

The Quick Roast is the product's **top-of-funnel acquisition hook**. It's designed to:

1. Give visitors an instant taste of the product's personality
2. Show enough value to motivate signup
3. Keep output short enough that full analysis still feels necessary

**How it works:**
1. Visitor pastes an idea (10-500 chars) on the homepage
2. `POST /api/quick-roast` sends it to Gemini 2.0 Flash (with Groq fallback)
3. Returns 3 sections: `first_impression`, `biggest_flaw`, `what_to_clarify`
4. Result is stored in DB (creates an `idea` with `is_quick_roast: true`)
5. A share link is generated so the visitor can share the roast
6. CTA: "Want the full analysis? Sign up to unlock all 7 dimensions."

**Rate limit:** 3 per hour per IP address (DB-backed, not in-memory).

---

## Local Development Setup

### Prerequisites

- **Node.js** 20+ (LTS recommended)
- **npm** (comes with Node.js)
- **Supabase CLI** (for local DB development) — [install guide](https://supabase.com/docs/guides/cli)
- **Git**

### Step-by-Step Setup

**1. Clone the repository:**
```bash
git clone <repo-url>
cd aiproshit
```

**2. Install dependencies:**
```bash
npm install
```

**3. Set up environment variables:**
```bash
cp .env.example .env.local
```
Then fill in your API keys (see Environment Variables section below).

**4. Set up Supabase:**

Option A — **Supabase Cloud (recommended for beginners):**
1. Create a project at [supabase.com](https://supabase.com)
2. Go to Project Settings → API to get your URL and keys
3. Go to SQL Editor and run each migration file in order:
   ```
   supabase/migrations/001_initial_schema.sql
   supabase/migrations/002_tier1_signal_sources.sql
   supabase/migrations/003_tier2_error_recovery.sql
   supabase/migrations/004_tier2_email_notifications.sql
   supabase/migrations/005_tier3_indexes.sql
   supabase/migrations/006_tier4_feedback.sql
   ```

Option B — **Supabase Local (for advanced users):**
```bash
supabase start
supabase db push
```

**5. Get API keys:**

| Service | Where to Get | Free Tier |
|---------|-------------|-----------|
| Supabase | [supabase.com](https://supabase.com) → Project Settings → API | 500MB DB, 50K MAU |
| Gemini | [aistudio.google.com](https://aistudio.google.com) → Get API Key | 15 RPM |
| Groq | [console.groq.com](https://console.groq.com) → API Keys | 30 RPM |
| Serper | [serper.dev](https://serper.dev) → Dashboard → API Key | 2,500 queries/month |
| SerpAPI | [serpapi.com](https://serpapi.com) → Dashboard → API Key | 100 queries/month |
| Stripe | [dashboard.stripe.com](https://dashboard.stripe.com) → Developers → API Keys | Test mode free |
| Resend | [resend.com](https://resend.com) → API Keys | 100 emails/day |
| Sentry | [sentry.io](https://sentry.io) → Settings → Client Keys | 5K events/month |

**6. Start the development server:**
```bash
npm run dev
```
Open [http://localhost:3000](http://localhost:3000).

### Environment Variables

**File:** `.env.local` (copy from `.env.example`)

```bash
# ─── Supabase (REQUIRED) ──────────────────────────────────────────────────
NEXT_PUBLIC_SUPABASE_URL=https://your-project.supabase.co  # Project URL from Supabase dashboard
NEXT_PUBLIC_SUPABASE_ANON_KEY=your-anon-key                # Public anon key (safe for client)
SUPABASE_SERVICE_ROLE_KEY=your-service-role-key             # Admin key (server-only, NEVER expose)

# ─── AI (REQUIRED) ──────────────────────────────────────────────────────
GEMINI_API_KEY=your-gemini-key    # Primary LLM. Get from aistudio.google.com
GROQ_API_KEY=your-groq-key        # Fallback LLM. Get from console.groq.com

# ─── Signal Providers (OPTIONAL - enhance analysis quality) ─────────────
SERPER_API_KEY=your-serper-key     # Web search. Get from serper.dev
SERPAPI_KEY=your-serpapi-key        # Google Trends. Get from serpapi.com

# ─── Payments (OPTIONAL - needed for billing) ───────────────────────────
NEXT_PUBLIC_STRIPE_PUBLISHABLE_KEY=pk_test_xxx   # Public Stripe key
STRIPE_SECRET_KEY=sk_test_xxx                     # Secret Stripe key
STRIPE_WEBHOOK_SECRET=whsec_xxx                   # Webhook signature secret

# ─── Email (OPTIONAL - needed for notifications) ────────────────────────
RESEND_API_KEY=re_xxx              # Email delivery. Get from resend.com

# ─── Monitoring (OPTIONAL) ───────────────────────────────────────────────
NEXT_PUBLIC_SENTRY_DSN=            # Sentry error tracking DSN
SENTRY_AUTH_TOKEN=                 # Sentry auth token for source maps

# ─── App ──────────────────────────────────────────────────────────────────
NEXT_PUBLIC_APP_URL=http://localhost:3000   # Your app's base URL
```

**Minimum viable setup:** You need Supabase + Gemini + Groq to run the core product. Everything else is optional and gracefully degrades.

### Running the App

```bash
# Development server (with hot reload)
npm run dev

# Type checking (catches TypeScript errors)
npm run type-check

# Linting
npm run lint

# Run tests
npm run test

# Run tests once (CI mode)
npm run test:ci

# Production build
npm run build

# Start production server
npm start
```

---

## Testing

**Framework:** Vitest (configured in `vitest.config.ts`)
**Environment:** Node.js
**Aliases:** `@` → `./src`

### What's Tested

| Test File | What It Tests | Tests |
|-----------|--------------|-------|
| `evidence-quantifier.test.ts` | Baseline computation from signal data | 8 |
| `vagueness-gate.test.ts` | Vagueness blocking logic and thresholds | 6 |
| `weighted-scorer.test.ts` | Score calculation with confidence weighting | 6 |
| `sanitize.test.ts` | HTML stripping, XSS prevention | 17 |
| `validators.test.ts` | Zod schema validation for API inputs | 5 |
| **Total** | | **42** |

### Running Tests

```bash
# Run all tests in watch mode
npm run test

# Run tests once (CI mode, no watch)
npm run test:ci

# Run specific test file
npx vitest run src/__tests__/lib/pipeline/evidence-quantifier.test.ts
```

---

## Deployment

### Vercel Setup

1. Connect your GitHub repository to Vercel
2. Set all environment variables in Vercel → Settings → Environment Variables
3. Deploy (Vercel auto-detects Next.js)

**Important Vercel constraints:**
- **10-second function timeout** on free tier (each pipeline step must complete within this)
- **Edge middleware** for auth token refresh
- **Serverless functions** for API routes (cold starts possible)

### CI/CD Pipeline

**File:** `.github/workflows/ci.yml`

Runs on every push to `main` and every PR targeting `main`:

```
1. npm ci            # Install dependencies
2. npm run lint      # ESLint
3. npm run type-check # TypeScript compilation check
4. npm run test:ci   # Vitest (run once, no watch)
5. npm run build     # Full Next.js build (catches build errors)
```

All 4 checks must pass for the pipeline to succeed.

---

## Key Architectural Decisions

These are the major decisions recorded in `docs/DECISIONS.md`. Each has a rationale and alternatives that were rejected.

| Decision | Choice | Why |
|----------|--------|-----|
| **DEC-009** | Client-driven sequential pipeline | Stays under Vercel 10s limit, no queue infra needed, natural progress tracking |
| **DEC-010** | 3 free credits on signup | Enough for one full loop: submit → clarify → get report |
| **DEC-011** | Modular signal provider interface | Adding new sources requires no pipeline changes |
| **DEC-012** | HackerNews over Reddit | Free Algolia API vs Reddit's paid API ($0.24/1K requests) |
| **DEC-016** | LLM inline classification (no dedicated ML model) | Simpler, zero infrastructure. DistilBERT deferred to Phase 11 |
| **DEC-020** | Evidence baselines with ±0.15 LLM constraint | Reproducibility — same signals produce same scores |
| **DEC-021** | Vagueness threshold at 0.7 | Blocks clearly vague ideas while allowing workable ones |
| **DEC-022** | Real URLs required in evidence refs | Prevents hallucinated sources in reports |
| **DEC-023** | Quick Roast teaser + paywall for full report | Drives conversion from free to paid |
| **DEC-024** | completed_steps[] array for retry | Enables resuming failed pipelines from the failed step |
| **DEC-027** | @react-pdf/renderer for PDF export | Client-side rendering, zero server cost, ~400KB lazy-loaded |
| **DEC-031** | Custom input sanitization + Zod validation | Strips HTML, blocks 13 prompt injection patterns, prevents XSS |

For the full list of 39 decisions with detailed rationale, see `docs/DECISIONS.md`.

---

## Project Status & Roadmap

### All 40 Build Phases — Completed

**PRD Phase 1 — End-to-End Analysis (Phases 1-7):**

| Phase | Scope | Completed |
|-------|-------|-----------|
| 1 | Foundation (Next.js, TypeScript, project structure) | 2026-03-22 |
| 2 | Database & Auth (Supabase schema, auth, RLS) | 2026-03-24 |
| 3 | Layouts, Marketing & Auth Pages (UI shells, auth forms) | 2026-03-24 |
| 4 | AI Infrastructure & Quick Roast (Gemini/Groq, quick roast) | 2026-03-24 |
| 5 | Full Analysis Pipeline (7-step with HackerNews signals) | 2026-03-24 |
| 6 | Idea Flow & Dashboard (submission wizard, dashboard, ideas list) | 2026-03-24 |
| 7 | Report Page (12-section report with all scoring/verdict details) | 2026-03-24 |

**PRD Phase 2 — Repeat Usage + Monetization (Phases 8-10):**

| Phase | Scope | Completed |
|-------|-------|-----------|
| 8 | Workspace & Compare (side-by-side 2-4 ideas with AI takeaway) | 2026-03-24 |
| 9 | Billing & Credits (Stripe INR pricing, credit packages) | 2026-03-25 |
| 10 | Share & Export (public share links for reports and roasts) | 2026-03-25 |

**PRD Phase 3 — Expansion (Phases 11-13):**

| Phase | Scope | Completed |
|-------|-------|-----------|
| 11 | ML Categorizer (LLM inline classification, 10-class taxonomy) | 2026-03-25 |
| 12 | Admin Panel (metrics, jobs, users, moderation, prompts) | 2026-03-25 |
| 13 | Polish & Deploy (responsive design, SEO, Vercel deployment) | 2026-03-28 |

**Tier 1 — Core Intelligence (Phases 14-19):**

| Phase | Scope | Completed |
|-------|-------|-----------|
| 14 | Real Web Search via Serper.dev (3 queries/analysis) | 2026-03-28 |
| 15 | Google Trends via SerpAPI (demand timing signals) | 2026-03-28 |
| 16 | Vagueness Blocking (threshold 0.7, mandatory clarification) | 2026-03-28 |
| 17 | Reproducible Scoring (evidence baselines, ±0.15 LLM constraint) | 2026-03-28 |
| 18 | Evidence Verification (real URLs, `[Unverified]` prefix for LLM) | 2026-03-28 |
| 19 | Usage Gating (teaser vs full report, paywall overlay) | 2026-03-28 |

**Tier 2 — Product Quality (Phases 20-27):**

| Phase | Scope | Completed |
|-------|-------|-----------|
| 20 | Error Recovery (completed_steps tracking, admin retry) | 2026-03-28 |
| 21 | Category Preservation (reuses category across reruns) | 2026-03-28 |
| 22 | Clarification Answers in Report (Q&A pairs visible) | 2026-03-28 |
| 23 | PDF Export (@react-pdf/renderer, client-side, lazy-loaded) | 2026-03-28 |
| 24 | Per-Route Error Boundaries (error.tsx in all 4 route groups) | 2026-03-28 |
| 25 | Per-User Rate Limiting (DB-backed, configurable tiers) | 2026-03-28 |
| 26 | Email Notifications (Resend, analysis completion) | 2026-03-28 |
| 27 | Input Sanitization (HTML strip, XSS prevention, prompt injection) | 2026-03-28 |

**Tier 3 — Infrastructure (Phases 28-34):**

| Phase | Scope | Completed |
|-------|-------|-----------|
| 28 | Structured Logging & Sentry (client, server, edge) | 2026-03-28 |
| 29 | Security Headers (CSP, X-Frame-Options, Permissions-Policy) | 2026-03-28 |
| 30 | Rate Limiting All APIs (18+ routes with DB-backed limits) | 2026-03-28 |
| 31 | DB Indexes + Webhook Hardening (6 indexes, Stripe idempotency) | 2026-03-28 |
| 32 | Environment Separation (proper .env structure) | 2026-03-28 |
| 33 | CI/CD Pipeline (GitHub Actions: lint, type-check, test, build) | 2026-03-28 |
| 34 | Test Coverage (Vitest: 5 test suites, 42 tests) | 2026-03-28 |

**Tier 4 — Polish (Phases 35-40):**

| Phase | Scope | Completed |
|-------|-------|-----------|
| 35 | SEO & Meta Tags (robots.ts, sitemap.ts, per-page metadata) | 2026-03-28 |
| 36 | Analytics (Vercel Analytics, 7 typed conversion events) | 2026-03-28 |
| 37 | Loading States & Onboarding (skeletons, empty states) | 2026-03-28 |
| 38 | Feedback Mechanism (rate-limited feedback API + UI) | 2026-03-28 |
| 39 | Optimistic UI & Accessibility (credit balance updates, ARIA) | 2026-03-28 |
| 40 | Mobile & Performance (responsive audit, lazy loading) | 2026-03-28 |

### Remaining Work (Tier 5 — Business Readiness)

These items are not code features but business/legal requirements needed before charging real money:

- [ ] Terms of Service page
- [ ] Privacy Policy page
- [ ] Refund policy (what happens if analysis fails after credit deduction)
- [ ] Credit expiry policy
- [ ] Support channel (email or ticketing)
- [ ] Abuse prevention (spam ideas, bot detection beyond rate limiting)
- [ ] Data retention policy
- [ ] Cookie consent (GDPR compliance)

---

## Documentation

All detailed docs live in `/docs/`:

| Document | Purpose |
|----------|---------|
| `killMyIdea_prd.pdf` | Product requirements (source of truth) |
| `EXECUTION_PLAN.md` | Phase-by-phase build plan with dependencies |
| `ARCHITECTURE.md` | Stack, structure, pipeline model |
| `DB_SCHEMA.md` | Database schema and constraints |
| `API_CONTRACTS.md` | All API endpoints with request/response shapes |
| `UI_MAP.md` | Routes, pages, components, states |
| `DECISIONS.md` | 39 technical decisions with rationale |
| `TASK_RULES.md` | Development discipline rules |
| `tiers.md` | Gap analysis across 5 tiers |
| `BACKUP_RECOVERY.md` | Data protection and recovery procedures |

---

## License

This project is private and not open-source.
