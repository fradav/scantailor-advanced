/*
    Scan Tailor - Interactive post-processing tool for scanned pages.
    Copyright (C)  Joseph Artsimovich <joseph.artsimovich@gmail.com>

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef OUTPUT_OPTIONSWIDGET_H_
#define OUTPUT_OPTIONSWIDGET_H_

#include "ui_OutputOptionsWidget.h"
#include "FilterOptionsWidget.h"
#include "IntrusivePtr.h"
#include "PageId.h"
#include "PageSelectionAccessor.h"
#include "ColorParams.h"
#include "DewarpingOptions.h"
#include "DepthPerception.h"
#include "DespeckleLevel.h"
#include "Dpi.h"
#include "ImageViewTab.h"
#include "Params.h"
#include "BinarizationOptionsWidget.h"
#include <set>
#include <QtWidgets/QStackedLayout>
#include <QtCore/QPointer>
#include <QtCore/QObjectCleanupHandler>
#include <memory>

namespace dewarping {
    class DistortionModel;
}

namespace output {
    class Settings;
    class DewarpingParams;

    class OptionsWidget : public FilterOptionsWidget, private Ui::OutputOptionsWidget {
    Q_OBJECT
    public:
        OptionsWidget(IntrusivePtr<Settings> const& settings, PageSelectionAccessor const& page_selection_accessor);

        virtual ~OptionsWidget();

        void preUpdateUI(PageId const& page_id);

        void postUpdateUI();

        ImageViewTab lastTab() const {
            return m_lastTab;
        }

        DepthPerception const& depthPerception() const {
            return m_depthPerception;
        }

    signals:

        void despeckleLevelChanged(DespeckleLevel level, bool* handled);

        void depthPerceptionChanged(double val);

    public slots:

        void tabChanged(ImageViewTab tab);

        void distortionModelChanged(dewarping::DistortionModel const& model);

    private slots:

        void changeDpiButtonClicked();

        void applyColorsButtonClicked();

        void applySplittingButtonClicked();

        void dpiChanged(std::set<PageId> const& pages, Dpi const& dpi);

        void applyColorsConfirmed(std::set<PageId> const& pages);

        void applySplittingOptionsConfirmed(std::set<PageId> const& pages);

        void colorModeChanged(int idx);

        void thresholdMethodChanged(int idx);

        void fillingColorChanged(int idx);

        void pictureShapeChanged(int idx);

        void tiffCompressionChanged(int idx);

        void cutMarginsToggled(bool checked);

        void equalizeIlluminationToggled(bool checked);

        void equalizeIlluminationColorToggled(bool checked);

        void savitzkyGolaySmoothingToggled(bool checked);

        void morphologicalSmoothingToggled(bool checked);

        void splittingToggled(bool checked);

        void bwForegroundToggled(bool checked);

        void colorForegroundToggled(bool checked);

        void binarizationSettingsChanged();

        void despeckleOffSelected();

        void despeckleCautiousSelected();

        void despeckleNormalSelected();

        void despeckleAggressiveSelected();

        void applyDespeckleButtonClicked();

        void applyDespeckleConfirmed(std::set<PageId> const& pages);

        void changeDewarpingButtonClicked();

        void dewarpingChanged(std::set<PageId> const& pages, DewarpingOptions const& opt);

        void applyDepthPerceptionButtonClicked();

        void applyDepthPerceptionConfirmed(std::set<PageId> const& pages);

        void depthPerceptionChangedSlot(int val);

        void binarizationOptionsChanged(int idx);

    private:
        void handleDespeckleLevelChange(DespeckleLevel level);

        void reloadIfNecessary();

        void updateDpiDisplay();

        void updateColorsDisplay();

        void updateDewarpingDisplay();

        void addBinarizationOptionsWidget(BinarizationOptionsWidget* widget);

        IntrusivePtr<Settings> m_ptrSettings;
        PageSelectionAccessor m_pageSelectionAccessor;
        PageId m_pageId;
        Dpi m_outputDpi;
        ColorParams m_colorParams;
        SplittingOptions m_splittingOptions;
        PictureShape m_pictureShape;
        DepthPerception m_depthPerception;
        DewarpingOptions m_dewarpingOptions;
        DespeckleLevel m_despeckleLevel;
        ImageViewTab m_lastTab;
    };
}  // namespace output
#endif  // ifndef OUTPUT_OPTIONSWIDGET_H_
